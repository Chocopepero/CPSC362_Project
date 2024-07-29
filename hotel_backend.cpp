#include "hotel_backend.hpp"
#include "json_util.hpp"
#include "room_db.hpp"
#include "user_db.hpp"

#include "server_utils/crow_all.h"
#include "server_utils/sessions.h"
#include "server_utils/rapidjson/document.h"     // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h" // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h" // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"


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
    int id = std::stoi(req.url_params.get("id"));

    auto res_it = _reservation_record.find(id);
    if (res_it == _reservation_record.end()) {
      res.code = 404;
      res.write("Reservation not found");
      res.end();
      return;
    }
    const Reservation &reservation = res_it->second;

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    SerializeReservationRecordToJSON(reservation, &writer);

    res.code = 200;
    res.set_header("Content-Type", "application/json");
    res.write(s.GetString());
    res.end();

  } catch (const std::exception &e) {
    res.code = 400;
    res.set_header("Content-Type", "application/json");
    crow::json::wvalue error_response;
    error_response["error"] =
        "Failed to retrieve reservation: " + std::string(e.what());
    res.write(error_response.dump());
  }
  res.end();
}

using Session = crow::SessionMiddleware<crow::InMemoryStore>;
crow::App<crow::CookieParser, Session> app{Session{
    crow::InMemoryStore{} // Using in-memory store for session data
}};

// API handler functions implementation
void HotelBackend::getUserDetails(const crow::request &req, crow::response &res) {
    auto &user_db = UserDB::instance();
    auto session = app.get_context<Session>(req);
    if (!session.get<bool>("authenticated", false)) {
      res.code = 401;
      res.write("Unauthorized");
      res.end();
      return;
    }
    auto username = session.get<std::string>("username ", "");
    User* user_ptr = user_db.find(username);
    if (user_ptr == nullptr) {
        res.code = 404;
        res.write("User not found");
        res.end();
        return;
    }
    User user = *user_ptr;
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("username");
    writer.String(user.get_username().c_str());
    writer.Key("email");
    writer.String(user.get_email().c_str());
    writer.Key("contact_info");
    writer.StartObject();
    writer.Key("name");
    writer.String(user.get_contact_info().getName().c_str());
    writer.Key("phone_number");
    writer.String(user.get_contact_info().getPhoneNumber().c_str());
    writer.EndObject();
    writer.Key("reservations");
    writer.StartArray();
    for (int res_id : user.get_reservations()) {
        writer.Int(res_id);
    }
    writer.EndArray();
    writer.EndObject();
    res.set_header("Content-Type", "application/json");
    res.write(s.GetString());
    res.end();
}

void HotelBackend::updateUsername(const crow::request &req, crow::response &res) {
    auto &user_db = UserDB::instance();
        auto& session = app.get_context<Session>(req);
    if (!session.get<bool>("authenticated", false)) {
        res.code = 401;
        res.write("Unauthorized");
        res.end();
        return;
    }
    auto body = crow::json::load(req.body);
    if (!body) {
        res.code = 400;
        res.write("Invalid JSON format");
        res.end();
        return;
    }
    auto username = session.get<std::string>("username", "");
    std::string new_username = body["username"].s();
    User* user = user_db.find(username);
    if (user == nullptr) {
        res.code = 404;
        res.write("User not found");
        res.end();
        return;
    }
    user->set_username(new_username);
    session.set("username", new_username);
    res.code = 200;
    res.write("Username updated successfully");
    res.end();
}

void HotelBackend::updateEmail(const crow::request &req, crow::response &res) {
    auto &user_db = UserDB::instance();
        auto& session = app.get_context<Session>(req);
    if (!session.get<bool>("authenticated", false)) {
        res.code = 401;
        res.write("Unauthorized");
        res.end();
        return;
    }
    auto body = crow::json::load(req.body);
    if (!body) {
        res.code = 400;
        res.write("Invalid JSON format");
        res.end();
        return;
    }
    auto username = session.get<std::string>("username", "");
    std::string new_email = body["email"].s();
    User* user = user_db.find(username);
    if (user == nullptr) {
        res.code = 404;
        res.write("User not found");
        res.end();
        return;
    }
    user->set_email(new_email);
    res.code = 200;
    res.write("Email updated successfully");
    res.end();
}

void HotelBackend::updatePassword(const crow::request &req, crow::response &res) {
    auto &user_db = UserDB::instance();
        auto& session = app.get_context<Session>(req);
    if (!session.get<bool>("authenticated", false)) {
        res.code = 401;
        res.write("Unauthorized");
        res.end();
        return;
    }
    auto body = crow::json::load(req.body);
    if (!body) {
        res.code = 400;
        res.write("Invalid JSON format");
        res.end();
        return;
    }
    auto username = session.get<std::string>("username", "");
    std::string new_password = body["password"].s();
    User* user = user_db.find(username);
    if (user == nullptr) {
        res.code = 404;
        res.write("User not found");
        res.end();
        return;
    }
    user->set_password(new_password);
    res.code = 200;
    res.write("Password updated successfully");
    res.end();
}

void HotelBackend::cancelReservation(const crow::request &req, crow::response &res) {
    auto &user_db = UserDB::instance();
        auto& session = app.get_context<Session>(req);
    if (!session.get<bool>("authenticated", false)) {
        res.code = 401;
        res.write("Unauthorized");
        res.end();
        return;
    }
    auto body = crow::json::load(req.body);
    if (!body) {
        res.code = 400;
        res.write("Invalid JSON format");
        res.end();
        return;
    }
    auto username = session.get<std::string>("username", "");
    int reservation_id = body["reservationId"].i();
    User* user = user_db.find(username);
    if (user == nullptr) {
        res.code = 404;
        res.write("User not found");
        res.end();
        return;
    }
    auto reservation = _reservation_record.find(reservation_id);
    if (reservation != _reservation_record.end())
    {
      res.code = 404;
      res.write("Reservation not found");
      res.end();
      return;
    }
    if (!user->Remove_Reservation(reservation->second)) {
        res.code = 500;
        res.write("Failed to cancel reservation");
        res.end();
        return;
    }
    _reservation_record.erase(reservation_id);
    res.code = 200;
    res.write("Reservation cancelled successfully");
    res.end();
}
