#pragma once

#include <string>
#include <map>

#include "reservation.hpp"

class HotelBackend {
public:
  HotelBackend(const std::string &reservation_records_filepath)
      : _reservation_records_filepath{reservation_records_filepath} {}

  bool LoadRecordsFromJSONFile();
  bool WriteRecordsToJSONFile() const;
  bool AssignRoom(int res_id);
  bool CheckOut(int room_id);

private:
  const std::string &_reservation_records_filepath;
  std::map<int, Reservation> _reservation_record;
};
