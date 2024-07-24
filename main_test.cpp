#include <string>

#include "hotel_backend.hpp"
// #include "room_db.hpp"
#include "user_db.hpp"

int main() {
  const std::string kFilename = "data/reservation_records.json";
  HotelBackend backend{kFilename};
  auto &user_db = UserDB::instance();
  // User user{};
  // std::stringstream stream{"username,password,email,name,phone,1,2,3,4"};
  // stream >> user;
  // user_db.test(user);
  for (auto user : user_db.TestMap()) {
    std::cout << user.first << "/" << user.second << '\n';
  };
  // auto &roomdatabase = RoomDatabase::instance();
  // ContactInfo guest("name", "number");
  // std::vector<std::pair<std::string, int>> beds{{"Queen", 2}};

  // Reservation test{1000, guest, 2, 3, 3, beds, true};
  // std::map<int, Reservation> reservation_record{};
  // reservation_record.insert({test.get_Reservation_Id(), test});
  // backend.set_map(reservation_record);
  // backend.LoadRecordsFromJSONFile();
}
