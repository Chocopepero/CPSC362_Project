#pragma once

#include <string>

#include "contactinfo.hpp"

class User {
public:
  // Confirm that the given information is unique and different.
  // If they are they same, return false and do not update the info.
  // If the info was updated, return true.
  bool change_contact_info(ContactInfo new_info)
  {
    if (_contact == new_info)
      return false;
    _contact = new_info;
    return true;
  }

  ContactInfo get_contact_info() { return _contact; }

  // Non-secure password validation for a particular user.
  // Can take either a username string or an email string.
  bool validate_login(std::string username_or_email, std::string password) {
    return ((_username == username_or_email || _email == username_or_email) && _password == password);
  }

private:
  std::string _username;
  std::string _password;
  std::string _email;
  ContactInfo _contact;
};
