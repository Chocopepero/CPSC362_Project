#include <string>
#include <utility>
#include <vector>

#include "contactinfo.hpp"
#include "user.hpp"

class reservation {
public:
  reservation() = delete;
  reservation(std::string name, std::string phone_number, int adults,
              int children, int rooms,
              std::vector<std::pair<std::string, int>> bed_types);
  reservation(ContactInfo reserving_guest, int adults, int children, int rooms,
              std::vector<std::pair<std::string, int>> _bed_types);
  ContactInfo get_Primary_Guest() { return _primary_guest; }
  int get_Reservation_Id() { return _reservation_id; }
  bool modify_Rooms();
  int fulfill_Reservation();

private:
  int generate_Reservation_Id();
  int _reservation_id;
  ContactInfo _primary_guest;
  int _num_of_adults;
  int _num_of_children;
  int _num_of_rooms;
  std::vector<std::pair<std::string, int>> _bed_types;
  bool _fulfillment_status;
};
