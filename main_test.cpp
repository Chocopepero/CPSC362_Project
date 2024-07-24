#include <string>

#include "hotel_backend.hpp"
// #include "room_db.hpp"

int main() {
  const std::string kFilename = "data/reservation_records.json";
  HotelBackend backend{kFilename};
  // auto &roomdatabase = RoomDatabase::instance();
  // ContactInfo guest("name", "number");
  // std::vector<std::pair<std::string, int>> beds{{"Queen", 2}};

  // Reservation test{1000, guest, 2, 3, 3, beds, true};
  // std::map<int, Reservation> reservation_record{};
  // reservation_record.insert({test.get_Reservation_Id(), test});
  // backend.set_map(reservation_record);
  backend.LoadRecordsFromJSONFile();

}
