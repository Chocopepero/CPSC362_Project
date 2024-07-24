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

   std::unordered_map<std::string, std::string> TestMap() { return _email_to_username; }
   void test(const User& user){
     _email_to_username.insert({user.get_email(), user.get_username()});
     _users.insert({user.get_username(), user});
   }

 private:
   UserDB(const std::string &filename);

   UserDB(const UserDB &) = delete;
   UserDB &operator=(const UserDB &) = delete;

   std::unordered_map<std::string, User> _users;
   std::unordered_map<std::string, std::string> _email_to_username;
};
