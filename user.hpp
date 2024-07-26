#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "contactinfo.hpp"
#include "reservation.hpp"
class Reservation;

class User {
public:
  // Confirm that the given information is unique and different.
  // If they are the same, return false and do not update the info.
  // If the info was updated, return true.
  bool change_contact_info(ContactInfo new_info);

  ContactInfo get_contact_info() const;
  std::vector<int> get_reservations() const;
  std::string get_username() const;
  std::string get_email() const;

  // To only be used when populating database
  void set_username(const std::string &username);
  void set_email(const std::string &email);
  void set_password(const std::string password);

  // Non-secure password validation for a particular user.
  // Can take either a username string or an email string.
  bool validate_login(std::string username_or_email, std::string password);

  void Add_Reservation(const Reservation &res);
  bool Remove_Reservation(const Reservation &res);

  friend std::istream &operator>>(std::istream &stream, User &user);
  friend std::ostream &operator<<(std::ostream &stream, User &user);

private:
  std::string _username;
  std::string _password;
  std::string _email;
  ContactInfo _contact;
  std::vector<int> _reservations;
};
