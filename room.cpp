#include <iostream>
#include <string>
#include <utility>

#include "room.hpp"

Room::Room(int room_id, std::string room_type, bool available,
           int registered_reservation_id)
    : _room_id{room_id}, _room_type{std::move(room_type)},
      _available{available},
      _registered_reservation_id{registered_reservation_id} {}

Room::~Room() noexcept = default;

Room::Room(Room const &other)
    : _room_id(other._room_id), _room_type(other._room_type),
      _available(other._available),
      _registered_reservation_id(other._registered_reservation_id) {}

Room::Room(Room &&other)
    : _room_id(std::move(other._room_id)),
      _room_type(std::move(other._room_type)),
      _available(std::move(other._available)),
      _registered_reservation_id(std::move(other._registered_reservation_id)) {}

Room & Room::operator=( Room const & rhs) & {
  if (&rhs == this) return *this;

  _room_id   = rhs._room_id;
  _room_type = rhs._room_type;
  _available = rhs._available;
  _registered_reservation_id = rhs._registered_reservation_id;

  return *this;
}

Room& Room::operator=( Room && rhs) & noexcept{
    if (&rhs == this) return *this;

  _room_id   = rhs._room_id;
  _room_type = std::move(rhs._room_type);
  _available = rhs._available;
  _registered_reservation_id = rhs._registered_reservation_id;

  return *this;
}

// .Dat file should be in format room_id, room_type in separate lines.
std::istream &operator>>(std::istream &stream, Room &room) {
  char delimiter;
  Room temp{};
  if (stream >> temp._room_id >> std::ws >> delimiter && delimiter == ',' &&
      stream >> temp._room_type) {
    room = std::move(temp);
  }
  else {
    stream.setstate(std::ios::failbit);
  }
  return stream;
}
