#include "reservation.hpp"
#include "user.hpp"

bool User::change_contact_info(ContactInfo new_info) {
  if (_contact == new_info)
    return false;
  _contact = new_info;
  return true;
}

ContactInfo User::get_contact_info() const { return _contact; }

std::vector<int> User::get_reservations() const { return _reservations; }

std::string User::get_username() const { return _username; }

std::string User::get_email() const { return _email; }

void User::set_username(const std::string &username) { _username = username; }

void User::set_email(const std::string &email) { _email = email; }

void User::set_password(const std::string password) { _password = password; }

bool User::validate_login(std::string username_or_email, std::string password) {
  return ((_username == username_or_email || _email == username_or_email) &&
          _password == password);
}

void User::Add_Reservation(const Reservation &res) {
  _reservations.push_back(res.get_Reservation_Id());
}

bool User::Remove_Reservation(const Reservation &res) {
  auto it = std::find(_reservations.begin(), _reservations.end(),
                      res.get_Reservation_Id());
  if (it != _reservations.end()) {
    _reservations.erase(it);
    return true;
  }
  return false;
}

std::istream &operator>>(std::istream &stream, User &user) {
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

std::ostream &operator<<(std::ostream &stream, User &user) {
  stream << user._username << "," << user._password << "," << user._email << ","
         << user._contact << ",";
  for (int id : user._reservations) {
    stream << id << ",";
  }
  return stream;
}
