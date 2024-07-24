#pragma once

#include <iostream>
#include <string>

class Room {
public:
  // Default constructor. If no parameters are input use defaults.
  Room(int room_id = 0,
       std::string room_type = {},
       bool available = true,
       int registered_reservation_id = 0);
  // Copy Operator
  Room &operator=(Room const &rhs) &;
  // Move Operator
  Room &operator=(Room &&rhs) & noexcept;
  // Copy Constructor
  Room(Room const &other);
  // Move Constructor
  Room(Room &&other);
  //Destructor
  ~Room() noexcept;

  int Get_Room_ID() const { return _room_id; }
  std::string Get_Room_Type() const { return _room_type; }
  bool Is_Available() const { return _available; }
  void Set_Available(bool status = true) { _available = status; }
  int Get_Reservation() const { return _registered_reservation_id; }
  void Set_Reservation(int reservation_to_set) {
    _registered_reservation_id = reservation_to_set;
    _available = false;
  }
  void Clear_Reservation() {
    _registered_reservation_id = 0;
    _available = true;
  }
  // Operator overload to read .dat file that lists all the rooms.
  friend std::istream &operator>>(std::istream &stream, Room &room);

private:
  int _room_id;
  std::string _room_type;
  bool _available;
  int _registered_reservation_id;
};
