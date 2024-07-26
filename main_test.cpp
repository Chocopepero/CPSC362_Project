#include <string>

#include "hotel_backend.hpp"
// #include "room_db.hpp"
#include "user_db.hpp"

int main() {
  const std::string kFilename = "data/reservation_records.json";
  HotelBackend backend{kFilename};
  auto &user_db = UserDB::instance();
  user_db.register_acc("user", "password", "email", "name", "phone");
}
