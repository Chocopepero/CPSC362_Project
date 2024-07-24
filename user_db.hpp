#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

#include "user.hpp"

class UserDB{
 public:
   static UserDB &instance();
   User *find(const std::string& username);
   std::size_t size() const;
   bool verify_login(const std::string &username, const std::string& password);
   bool register_acc(const std::string &username, const std::string &password, const std::string &email);

 private:
   UserDB(const std::string &filename);

   UserDB(const UserDB &) = delete;
   UserDB &operator=(const UserDB &) = delete;

   std::unordered_map<std::string, User> _users;
   std::unordered_map<std::string, std::string> _email_to_username;
};
