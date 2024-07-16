#include <string>

#include "contactinfo.hpp"

class User {
 public:
   bool change_contact_info(ContactInfo new_info);

 private:
   std::string username;
   std::string password;
   bool member;
   std::string email;
   ContactInfo contact;
};
