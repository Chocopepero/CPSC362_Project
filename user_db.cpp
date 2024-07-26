#include <filesystem>
#include <fstream>

#include "user.hpp"
#include "user_db.hpp"

UserDB &UserDB::instance() {
  auto getFileName = []() {
    std::string filename;
    if (filename = "data/UserDB.dat"; std::filesystem::exists(filename))
      ;
    else
      filename.clear();

    return filename;
  };

  static UserDB theInstance(getFileName());
  return theInstance;
}

UserDB::UserDB(const std::string &filename) {
  std::ifstream fin(filename);
  if (!fin.is_open())
    std::cerr << "Warning: Could not open room list .dat file. Proceeding with "
                 "empty list\n";
  User tempUser{};
  std::string line;
  while (std::getline(fin, line)) {
    std::istringstream lineStream(line);
    lineStream >> tempUser;
    if (lineStream.fail()) {
      std::cerr << "Error: Failed to parse user data: " << line << "\n";
      continue;
    }

    _email_to_username[tempUser.get_email()] = tempUser.get_username();
    _users[tempUser.get_username()] = std::move(tempUser);
  }
}

User *UserDB::find(const std::string &username) {
  std::string user_or_email;
  auto email = _email_to_username.find(username);
  if (email == _email_to_username.end()) {
    user_or_email = username;
  } else {
    user_or_email = _email_to_username.find(username)->second;
  }
  auto result = _users.find(user_or_email);
  if (result == _users.end()) {
    return nullptr;
  }
  return &result->second;
}

std::size_t UserDB::size() const { return _users.size(); }

bool UserDB::verify_login(const std::string &username,
                          const std::string &password) {
  auto user = find(username);
  if (user == nullptr) {
    return false;
  }
  return user->validate_login(username, password);
}

bool UserDB::register_acc(const std::string &username,
                          const std::string &password, const std::string &email,
                          const std::string &name,
                          const std::string &phone_num) {
  if (find(username) != nullptr) {
    std::cerr << "Username already exists";
    return false;
  }
  if (find(email) != nullptr) {
    std::cerr << "Email already associated to account";
    return false;
  }
  ContactInfo new_info{name, phone_num};
  User new_user{};
  new_user.set_email(email);
  new_user.set_username(username);
  new_user.set_password(password);
  new_user.change_contact_info(new_info);

  std::ofstream user_file("data/UserDB.dat", std::ios_base::app);
  std::cout << "Write to UserDB.dat";
  user_file << new_user;

  _email_to_username.insert({email, username});
  _users.insert({username, std::move(new_user)});

  return true;
}
