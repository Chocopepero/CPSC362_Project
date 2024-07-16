#include <string>

class Address {
public:
  Address() = delete;
  Address(const std::string &street, const std::string &city,
          const std::string &state, int postal_code, const std::string &country)
      : _street{street}, _city{city}, _state{state}, _postal_code{postal_code},
        _country{country} {}

  Address(const Address &other)
      : _street{other._street}, _city{other._city}, _state{other._state},
        _postal_code{other._postal_code}, _country{other._country} {}

  bool ChangeAddress(Address new_address) {
    _street = new_address._street,
    _city = new_address._city,
    _state = new_address._state,
    _postal_code = new_address._postal_code,
    _country = new_address._country;
    return (*this == new_address);
  }

  bool operator==(const const Address &address_to_compare) {
    if (_street == address_to_compare._street &&
        _city == address_to_compare._city &&
        _state == address_to_compare._state &&
        _postal_code == address_to_compare._postal_code &&
        _country == address_to_compare._country)
      return true;
    else
      return false;
  }

private:
  std::string _street;
  std::string _city;
  std::string _state;
  int _postal_code;
  std::string _country;
};
