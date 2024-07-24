#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "contactinfo.hpp"

class User {
public:
  // Confirm that the given information is unique and different.
  // If they are they same, return false and do not update the info.
  // If the info was updated, return true.
  bool change_contact_info(ContactInfo new_info) {
    if (_contact == new_info)
      return false;
    _contact = new_info;
    return true;
  }

  ContactInfo get_contact_info() const { return _contact; }
  std::vector<int> get_reservations() const { return _reservations; }
  std::string get_username() const { return _username; }
  std::string get_email() const { return _email; }

  // To only be used when populating database
  void set_username(const std::string &username) { _username = username; }
  void set_email(const std::string &email) { _email = email; }
  void set_password(const std::string password) { _password = password; }

  // Non-secure password validation for a particular user.
  // Can take either a username string or an email string.
  bool validate_login(std::string username_or_email, std::string password) {
    return ((_username == username_or_email || _email == username_or_email) &&
            _password == password);
  }

  friend std::istream &operator>>(std::istream &stream, User &user) {
    std::string reservations_str;
    std::string contact;


    // Extract fields
    if (std::getline(stream, user._username, ',') &&
        std::getline(stream, user._password, ',') &&
        std::getline(stream, user._email, ',') &&
        std::getline(stream, contact, ',') &&
        std::getline(stream, reservations_str)) {

      std::istringstream contactStream(contact);
      contactStream >> user._contact;

      // Parse reservations
      std::istringstream resStream(reservations_str);
      int res_id;
      user._reservations.clear();
      while (resStream >> res_id) {
        user._reservations.push_back(res_id);
        if (resStream.peek() == ',') {
          resStream.ignore();
        } else {
          break;
        }
      }

      return stream;
    } else {
      stream.setstate(std::ios::failbit);
      return stream;
    }
  }

friend std::ostream &operator<<(std::ostream &stream, User &user){
  stream << user._username << "," << user._password << "," << user._email << "," << user._contact << ",";
  for(int id: user._reservations){
    stream << id << ",";
  }
  return stream;
}

private:
  std::string _username;
  std::string _password;
  std::string _email;
  ContactInfo _contact;
  std::vector<int> _reservations;
};
