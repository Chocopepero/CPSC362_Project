#pragma once

#include <istream>
#include <string>

// #include "address.hpp"

class ContactInfo {
public:
  // ContactInfo() = default;
  ContactInfo(const std::string &name = "",
              const std::string &phone_number = "")
      : _name{name}, _phone_number{phone_number} {}

  bool updateName(const std::string &name) {
    _name = name;
    return _name == name;
  }
  bool updatePhoneNumber(const std::string &phone_number) {
    _phone_number = phone_number;
    return _phone_number == phone_number;
  }

  // bool updateAddress(const std::string &street, const std::string &city,
  //                    const std::string &state, int postal_code,
  //                    const std::string &country) {
  //   Address new_address(street, city, state, postal_code, country);
  //   _address = new_address;
  //   return _address == new_address;
  // }

  // bool updateAddress(const Address &address) {
  //   _address = address;
  //   return true;
  // }

  bool operator==(const ContactInfo &other) {
    return (_name == other._name && _phone_number == other._phone_number);
  }

  // friend std::istream &operator>>(std::istream &stream, ContactInfo &info) {
  //   char delimiter;
  //   ContactInfo temp{};
  //   if (stream >> temp._name >> std::ws >> delimiter && delimiter == ',' &&
  //       stream >> temp._phone_number >> std::ws >> delimiter &&
  //       delimiter == ',') {
  //     info = std::move(temp);
  //   }

  //   else {
  //     stream.setstate(std::ios::failbit);
  //   }
  //   return stream;
  // }

  friend std::istream &operator>>(std::istream &stream, ContactInfo &info) {
    std::string name;
    std::string phone_number;

    // Extract name
    if (!std::getline(stream, name, ',')) {
      stream.setstate(std::ios::failbit);
      return stream;
    }
    info._name = name;

    // Extract phone_number
    if (!std::getline(stream, phone_number, ',')) {
      stream.setstate(std::ios::failbit);
      return stream;
    }
    info._phone_number = phone_number;

    return stream;
  }
  friend std::ostream &operator<<(std::ostream &stream, ContactInfo &info) {
    return stream << info._name << "," << info._phone_number;
  }

  std::string getName() const { return _name; }
  std::string getPhoneNumber() const { return _phone_number; }
  // Address getAddress() const { return _address; }

private:
  std::string _name;
  std::string _phone_number;
  // Address _address;
};
