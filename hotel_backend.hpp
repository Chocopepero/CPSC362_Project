#pragma once

#include <map>
#include <string>

#include "reservation.hpp"
#include "server_utils/crow_all.h"

// Declaration of HotelBackend class
class HotelBackend {
public:
  HotelBackend(const std::string &reservation_records_filepath)
      : _reservation_records_filepath{reservation_records_filepath} {}

  bool LoadRecordsFromJSONFile();
  bool WriteRecordsToJSONFile() const;
  bool AssignRoom(int res_id);
  bool CheckOut(int room_id);
  std::pair<bool, int> CreateReservation(const std::string &name, const std::string &phone,
                                         int adults, int children, int number_rooms,
                                         const Date &arrive, const Date &depart,
                                         const std::string &type);

  void getReservation(const crow::request &req, crow::response &res);

  // API Handler Functions
  void getUserDetails(const crow::request &req, crow::response &res);
  void updateUsername(const crow::request &req, crow::response &res);
  void updateEmail(const crow::request &req, crow::response &res);
  void updatePassword(const crow::request &req, crow::response &res);
  void cancelReservation(const crow::request &req, crow::response &res);

private:
  const std::string &_reservation_records_filepath;
  std::map<int, Reservation> _reservation_record;
};

#endif // API_HANDLERS_HPP
