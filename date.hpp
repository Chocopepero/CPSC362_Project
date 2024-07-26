#pragma once

#include <string>

class Date {
public:
  Date(const std::string &month = "1", const std::string &day = "1",
       const std::string &year = "1970")
      : _month{month}, _day{day}, _year{year} {}

  std::weak_ordering operator<=>(const Date &rhs) const noexcept {
    auto result = _year <=> rhs._year;
    if (result != 0) {
      return result;
    }
    result = _month <=> rhs._month;
    if (result != 0) {
      return result;
    }
    result = _day <=> rhs._day;
    if (result != 0) {
      return result;
    }
    return (std::weak_ordering::equivalent);
  }

  bool operator==(const Date &rhs) const noexcept {
    return (_month == rhs._month && _day == rhs._day && _year == rhs._year);
  }

private:
  std::string _month;
  std::string _day;
  std::string _year;
};
