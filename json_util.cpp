#include <string>
#include <vector>

#include "contactinfo.hpp"
#include "date.hpp"
#include "server_utils/rapidjson/document.h"     // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h" // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h" // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"
#include "reservation.hpp"

void SerializeContactToJSON(
    const ContactInfo &contact,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->Key("_name");
  writer->String(contact.getName().c_str());

  writer->Key("_phone_number");
  writer->String(contact.getPhoneNumber().c_str());

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

Date DeserializeDateFromJSON(const rapidjson::Value &json) {
  int year = json["_year"].GetInt();
  int month = json["_month"].GetInt();
  int day = json["_day"].GetInt();
  Date date{month, day, year};
  return date;
}

ContactInfo DeserializeContactFromJSON(const rapidjson::Value &json) {
  std::string name = json["_name"].GetString();
  std::string phoneNumber = json["_phone_number"].GetString();
  ContactInfo contact{name, phoneNumber};

  return contact;
}

Reservation DeserializeReservationFromJSON(const rapidjson::Value &json) {
  int reservationId = json["_reservation_id"].GetInt();
  ContactInfo primaryGuest = DeserializeContactFromJSON(json["_primary_guest"]);
  int numOfAdults = json["_num_of_adults"].GetInt();
  int numOfChildren = json["_num_of_children"].GetInt();
  int numOfRooms = json["_num_of_rooms"].GetInt();
  Date arrival = DeserializeDateFromJSON(json["_arrival"]);
  Date departure = DeserializeDateFromJSON(json["_departure"]);
  auto bedTypes = DeserializeVectorOfPairsFromJSON(json["_bed_types"]);
  bool fulfillmentStatus = json["_fulfillment_status"].GetBool();

  Reservation reservation(reservationId, primaryGuest, numOfAdults,
                          numOfChildren, numOfRooms, bedTypes,
                          fulfillmentStatus, arrival, departure);

  return reservation;
}
