#include <iostream>

#include "hotel_backend.hpp"
#include "room_db.hpp"

int main() {
  const std::string kFilename = "data/reservation_records.json";
  HotelBackend backend{kFilename};
  auto &roomdatabase = RoomDatabase::instance();
}
