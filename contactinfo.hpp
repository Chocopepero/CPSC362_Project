#pragma once

#include <string>

#include "address.hpp"

class ContactInfo {
public:
  // ContactInfo() = default;
  ContactInfo(const std::string &name = "", const std::string &phone_number = "",
              const std::string &street = "", const std::string &city = "",
              const std::string &state = "", int postal_code = -1,
              const std::string &country = "")
      : _name{name}, _phone_number{phone_number},
        _address(street, city, state, postal_code, country) {}

  bool updateName(const std::string &name) {
    _name = name;
    return _name == name;
  }
  bool updatePhoneNumber(const std::string &phone_number) {
    _phone_number = phone_number;
    return _phone_number == phone_number;
  }

  bool updateAddress(const std::string &street, const std::string &city,
                     const std::string &state, int postal_code,
                     const std::string &country) {
    Address new_address(street, city, state, postal_code, country);
    _address = new_address;
    return _address == new_address;
  }

  bool updateAddress(const Address& address){
    _address = address;
  }

  bool operator==(const ContactInfo &other) {
    return (_name == other._name && _phone_number == other._phone_number &&
            _address == other._address);
  }

  std::string getName() const { return _name; }
  std::string getPhoneNumber() const { return _phone_number; }
  Address getAddress() const { return _address; }

private:
  std::string _name;
  std::string _phone_number;
  Address _address;
};
