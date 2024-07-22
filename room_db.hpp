#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

#include "room.hpp"

class RoomDatabase {
public:
  static RoomDatabase &instance();
  Room *find(const int room_id);
  std::size_t size() const;

private:
  RoomDatabase(const std::string &filename);

  RoomDatabase(const RoomDatabase &) = delete;
  RoomDatabase &operator=(const RoomDatabase &) = delete;

  std::unordered_map<int, Room> _rooms;
};
