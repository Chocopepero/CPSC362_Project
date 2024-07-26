#include "hotel_backend.hpp"
#include "room_db.hpp"

#include <filesystem>
#include <fstream>

#include "server_utils/rapidjson/document.h"     // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h" // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h" // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"

void SerializeContactToJSON(
    const ContactInfo &contact,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->Key("_name");
  writer->String(contact.getName().c_str());

  writer->Key("_phone_number");
  writer->String(contact.getPhoneNumber().c_str());

  // writer->Key("_address");
  // writer->String(contact.getAddress().address_As_String().c_str());

  writer->EndObject();
}
void SerializeDateToJSON(const Date &date,
                         rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();
  writer->Key("_year");
  writer->Int(date.get_Year());

  writer->Key("_month");
  writer->Int(date.get_Month());

  writer->Key("_day");
  writer->Int(date.get_Day());

  writer->EndObject();
}

void SerializeVectorOfPairsToJSON(
    const std::vector<std::pair<std::string, int>> &vec,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartArray();
  for (const auto &pair : vec) {
    writer->StartObject();

    writer->Key("Type");
    writer->String(pair.first.c_str());

    writer->Key("Num");
    writer->Int(pair.second);

    writer->EndObject();
  }
  writer->EndArray();
}

void SerializeReservationRecordToJSON(
    const Reservation &reservation,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->Key("_reservation_id");
  writer->Int(reservation.get_Reservation_Id());

  writer->Key("_primary_guest");
  SerializeContactToJSON(reservation.get_Primary_Guest(), writer);

  writer->Key("_num_of_adults");
  writer->Int(reservation.get_Num_of_Adults());

  writer->Key("_num_of_children");
  writer->Int(reservation.get_Num_of_Children());

  writer->Key("_num_of_rooms");
  writer->Int(reservation.get_Num_of_Rooms());

  writer->Key("_arrival");
  SerializeDateToJSON(reservation.get_Arrival(), writer);

  writer->Key("_departure");
  SerializeDateToJSON(reservation.get_Departure(), writer);

  writer->Key("_bed_types");
  SerializeVectorOfPairsToJSON(reservation.get_Bed_Types(), writer);

  writer->Key("_fulfillment_status");
  writer->Bool(reservation.get_Fulfillment_Status());
  writer->EndObject();
}

std::vector<std::pair<std::string, int>>
DeserializeVectorOfPairsFromJSON(const rapidjson::Value &json) {
  std::vector<std::pair<std::string, int>> vec;

  for (auto &v : json.GetArray()) {
    std::string type = v["Type"].GetString();
    int num = v["Num"].GetInt();
    vec.emplace_back(type, num);
  }
  return vec;
}

ContactInfo DeserializeContactFromJSON(const rapidjson::Value &json) {
  std::string name = json["_name"].GetString();
  std::string phoneNumber = json["_phone_number"].GetString();
  // std::string addressString = json["_address"].GetString();

  // std::stringstream ss(addressString);
  // Address address{};
  // ss >> address;
  ContactInfo contact{name, phoneNumber};
  // contact.updateAddress(address);

  return contact;
}

Reservation DeserializeReservationFromJSON(const rapidjson::Value &json) {
  int reservationId = json["_reservation_id"].GetInt();
  ContactInfo primaryGuest = DeserializeContactFromJSON(json["_primary_guest"]);
  int numOfAdults = json["_num_of_adults"].GetInt();
  int numOfChildren = json["_num_of_children"].GetInt();
  int numOfRooms = json["_num_of_rooms"].GetInt();
  auto bedTypes = DeserializeVectorOfPairsFromJSON(json["_bed_types"]);
  bool fulfillmentStatus = json["_fulfillment_status"].GetBool();

  Reservation reservation(reservationId, primaryGuest, numOfAdults,
                          numOfChildren, numOfRooms, bedTypes,
                          fulfillmentStatus);

  return reservation;
}

bool HotelBackend::WriteRecordsToJSONFile() const {
  std::ofstream records_file{_reservation_records_filepath};
  rapidjson::StringBuffer ss;
  rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
  writer.StartArray();
  for (auto reservation : _reservation_record) {
    SerializeReservationRecordToJSON(reservation.second, &writer);
  }
  writer.EndArray();

  records_file << ss.GetString();

  records_file.flush();
  records_file.close();
  return true;
}

bool HotelBackend::LoadRecordsFromJSONFile() {
  std::ifstream records_file{_reservation_records_filepath};
  if (!records_file.is_open()) {
    std::cerr << "Could not open file for reading: "
              << _reservation_records_filepath << std::endl;
    return false;
  }

  std::string jsonString((std::istreambuf_iterator<char>(records_file)),
                         std::istreambuf_iterator<char>());
  rapidjson::Document doc;
  doc.Parse(jsonString.c_str());

  if (!doc.IsArray()) {
    std::cerr << "Invalid JSON format in file: "
              << _reservation_records_filepath << std::endl;
    return false;
  }

  _reservation_record.clear();

  for (auto &reservationJSON : doc.GetArray()) {
    Reservation reservation = DeserializeReservationFromJSON(reservationJSON);
    _reservation_record[reservation.get_Reservation_Id()] = reservation;
  }
  return true;
}

bool HotelBackend::AssignRoom(int res_id) {
  auto reserve = _reservation_record.find(res_id);
  if (reserve == _reservation_record.end())
    return false;

  const std::string bed_type = reserve->second.get_Bed_Types().at(0).first;
  auto &room_db = RoomDatabase::instance();
  int open_room = room_db.first_open_room(bed_type);

  // If the return value of first open room is 0, there is no open room or we
  // failed to find one.
  if (!open_room) {
    return false;
  }

  _reservation_record.at(res_id).fulfill_Reservation(*room_db.find(open_room));
  return true;
}

bool HotelBackend::CheckOut(int room_id) {
  auto &room_db = RoomDatabase::instance();
  auto room = room_db.find(room_id);
  if (room == nullptr) {
    return false;
  }
  int res_id = room->Get_Reservation();
  _reservation_record.erase(res_id);
  room->Clear_Reservation();
  return true;
}

std::pair<bool, int> HotelBackend::CreateReservation(
    const std::string &name, const std::string &phone, int adults, int children,
    int number_rooms, const Date &arrive, const Date &depart,
    const std::string &type) {
  Reservation new_res{name,
                      phone,
                      adults,
                      children,
                      number_rooms,
                      {{type, number_rooms}},
                      _reservation_record,
                      arrive,
                      depart};
  WriteRecordsToJSONFile();
  return {true, new_res.get_Reservation_Id()};
}

void HotelBackend::getReservation(const crow::request &req,
                                  crow::response &res) {
  try {
    // Extract the reservation ID from the query parameters
    int id = std::stoi(req.url_params.get("id"));

    // Fetch the reservation
    auto res_it = _reservation_record.find(id);
    if (res_it == _reservation_record.end()) {
      res.code = 404; // Not Found
      res.write("Reservation not found");
      res.end();
      return;
    }
    const Reservation &reservation = res_it->second;

    // Serialize the reservation to JSON
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    SerializeReservationRecordToJSON(reservation, &writer);

    // Set response code and content
    res.code = 200; // OK
    res.set_header("Content-Type", "application/json");
    res.write(s.GetString());
    res.end();

  } catch (const std::exception &e) {
    // Handle errors (e.g., invalid ID, missing reservation)
    res.code = 400; // Bad Request
    res.set_header("Content-Type", "application/json");
    crow::json::wvalue error_response;
    error_response["error"] =
        "Failed to retrieve reservation: " + std::string(e.what());
    res.write(error_response.dump());
  }
  res.end();
}
