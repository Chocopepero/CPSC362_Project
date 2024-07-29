#pragma once

#include <compare>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "contactinfo.hpp"
#include "date.hpp"
#include "room.hpp"
#include "user.hpp"

class Reservation {
public:
  // Default constructor should not be used.
  Reservation() = default;

  // Constructor with reservation ID for data-base populating purposes.
  // Does NOT call GenerateID function.
  Reservation(int reservation_id, ContactInfo reserving_guest, int adults,
              int children, int rooms,
              std::vector<std::pair<std::string, int>> bed_types,
              bool fulfillmentStatus, const Date &arrival,
              const Date &departure);

  // Constructor for users with no account or contact info. A name and phone
  // number is still required in order for the ContactInfo class to initialize.
  Reservation(std::string name, std::string phone_number, int adults,
              int children, int rooms,
              std::vector<std::pair<std::string, int>> bed_types,
              std::map<int, Reservation> &reservations, const Date &arrival,
              const Date &departure);

  // Constructor for users with an account. Get that user's contact info.
  Reservation(ContactInfo reserving_guest, int adults, int children, int rooms,
              std::vector<std::pair<std::string, int>> bed_types,
              std::map<int, Reservation> &reservations, const Date &arrival,
              const Date &departure);

  ContactInfo get_Primary_Guest() const { return _primary_guest; }
  void set_Primary_Guest(ContactInfo guest) { _primary_guest = guest; }

  int get_Reservation_Id() const { return _reservation_id; }
  int get_Num_of_Adults() const { return _num_of_adults; }
  int get_Num_of_Children() const { return _num_of_children; }
  int get_Num_of_Rooms() const { return _num_of_rooms; }
  std::vector<std::pair<std::string, int>> get_Bed_Types() const {
    return _bed_types;
  }
  bool get_Fulfillment_Status() const { return _fulfillment_status; }
  Date get_Arrival() const { return _arrival; }
  Date get_Departure() const { return _departure; }

  void set_Reservation_ID(int num) { _reservation_id = num; }
  void set_Num_of_Adults(int num) { _num_of_adults = num; }
  void set_Num_of_Children(int num) { _num_of_children = num; }
  void set_Num_of_Rooms(int num) { _num_of_rooms = num; }
  void set_Bed_Types(std::vector<std::pair<std::string, int>> beds) {
    _bed_types = beds;
  }
  void set_Fulfillment_Status(bool status) { _fulfillment_status = status; }
  void set_Dates(const Date &arr, const Date &dep) {
    _arrival = arr;
    _departure = dep;
  }

  // This function is designed to accept a vector full of pairs that hold
  // the room type in first and the quantity in second.
  // When this vector is generated, it should be designed in a way that
  // ensure the order of these pairs are the same.
  bool modify_Rooms(std::vector<std::pair<std::string, int>> new_rooms) {
    if (_bed_types == new_rooms)
      return false;
    _bed_types = new_rooms;
    return true;
  }

  // Leave reservation fulfillment to reservation class. Reservation objects
  // will pass their own ID numbers to the room that is put as the parameter.
  bool fulfill_Reservation(Room &room);

private:
  std::pair<int, Reservation>
  generate_Reservation_Id(std::map<int, Reservation> &reservations);
  int _reservation_id;
  ContactInfo _primary_guest;
  int _num_of_adults;
  int _num_of_children;
  int _num_of_rooms;
  Date _arrival;
  Date _departure;
  std::vector<std::pair<std::string, int>> _bed_types;
  bool _fulfillment_status;
};
