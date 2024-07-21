#include <iostream>

#include "hotel_backend.hpp"

int main() {
  const std::string kFilename = "data/reservation_records.json";
  HotelBackend backend{kFilename};
  std::vector<std::pair<std::string, int>> beds{{"Queen", 1}};
  std::map<int, Reservation> testdatabase;
  Reservation test{
      "name",
      "1234",
      1,
      2,
      3,
      beds, testdatabase};
  testdatabase.insert({test.get_Reservation_Id(), test});
  backend.set_map(testdatabase);
  backend.WriteRecordsToJSONFile();
}
