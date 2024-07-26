#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "room.hpp"
#include "room_db.hpp"

// Return a reference to the one and only instance of the database
RoomDatabase& RoomDatabase::instance(){
  auto getFileName = []()
  {
    std::string filename;
    if (filename = "data/RoomList.dat"; std::filesystem::exists(filename));
    else filename.clear();

    return filename;
  };

  static RoomDatabase theInstance(getFileName());
  return theInstance;
}

RoomDatabase::RoomDatabase( const std::string& filename){
  std::ifstream fin(filename);
  if(!fin.is_open()) std::cerr << "Warning: Could not open room list .dat file. Proceeding with empty list\n";
  Room tempRoom{};
  while (fin >> tempRoom){
    _rooms.insert({tempRoom.Get_Room_ID(), std::move(tempRoom)});
  }
}

Room* RoomDatabase::find(const int room_id){
  auto result = _rooms.find(room_id);
  if ( result == _rooms.end()) return nullptr;
  return &result->second;
}

std::size_t RoomDatabase::size() const { return _rooms.size(); }

int RoomDatabase::first_open_room(const std::string &room_type){
  int s, e;
  if(room_type == "Standard"){
    s = 1;
    e = 4;
  } else if(room_type == "Deluxe"){
    s = 5;
    e = 8;
  } else if(room_type == "Suite"){
    s = 9;
    e = 10;
  } else{ return 0; }
  while(s <= e){
    if(find(s)->Is_Available()) {return s;}
    ++s;
  }
}
