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

  // Function to set the map up for JSON testing
  // REMOVE BEFORE FINAL SUBMISSION
  void set_map(std::map<int, Reservation> reservation_record) { _reservation_record = reservation_record; }

private:
  const std::string &_reservation_records_filepath;
  std::map<int, Reservation> _reservation_record;
};
