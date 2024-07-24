#include "reservation.hpp"

Reservation::Reservation(std::string name, std::string phone_number, int adults,
                         int children, int rooms,
                         std::vector<std::pair<std::string, int>> bed_types,
                         std::map<int, Reservation> &reservations)
    : _primary_guest(name, phone_number), _num_of_adults{adults},
      _num_of_children{children}, _num_of_rooms{rooms}, _bed_types{bed_types} {
  generate_Reservation_Id(reservations);
};

Reservation::Reservation(ContactInfo reserving_guest, int adults, int children,
                         int rooms,
                         std::vector<std::pair<std::string, int>> bed_types,
                         std::map<int, Reservation> &reservations)
    : _primary_guest{reserving_guest}, _num_of_adults{adults},
      _num_of_children{children}, _num_of_rooms{rooms}, _bed_types{bed_types} {
  generate_Reservation_Id(reservations);
};

Reservation::Reservation(int reservation_id, ContactInfo reserving_guest,
                         int adults, int children, int rooms,
                         std::vector<std::pair<std::string, int>> bed_types,
                         bool fulfillmentStatus)
    : _reservation_id{reservation_id}, _primary_guest(reserving_guest),
      _num_of_adults{adults}, _num_of_children{children}, _num_of_rooms{rooms},
      _bed_types{bed_types}, _fulfillment_status{fulfillmentStatus} {};

int Reservation::generate_Reservation_Id(
    std::map<int, Reservation> &reservations) {
  int new_reservation = 0;
  while (new_reservation == 0 ||
         reservations.find(new_reservation) != reservations.end()) {
    new_reservation = std::rand();
  }
  reservations.insert({new_reservation, *this});
  _reservation_id = new_reservation;
  return new_reservation;
}

bool Reservation::fulfill_Reservation(Room &room) {
  if (!_fulfillment_status) {
    room.Set_Reservation(_reservation_id);
    room.Set_Available(false);
    _fulfillment_status = true;
    return true;
  }
  return false;
}
