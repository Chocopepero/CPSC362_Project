#include "user_db.hpp"
#include "server_utils/crow_all.h"

void createUser(const crow::request &req, crow::response &res) {
  auto &user_db = UserDB::instance();
  try {
    std::cout << "Received createUser request" << std::endl;
    // Parse JSON request body
    auto body = crow::json::load(req.body);
    if (!body) {
      res.code = 400; // Bad Request
      res.write("Invalid JSON format");
      res.end();
      return;
    }

    // Extract user details from JSON
    std::string username = body["username"].s();
    std::string password = body["password"].s();
    std::string email = body["email"].s();
    std::string name = body["name"].s();
    std::string phone_num = body["phone_num"].s();

    // Validate input
    if (username.empty() || password.empty() || email.empty() || name.empty() ||
        phone_num.empty()) {
      res.code = 400; // Bad Request
      res.write("Missing required fields");
      res.end();
      return;
    }

    // Add the new user to the database
    bool success =
        user_db.register_acc(username, password, email, name, phone_num);
    if (!success) {
      res.code = 500; // Internal Server Error
      res.write("Failed to register user");
      res.end();
      return;
    }
    std::cout << "User registered successfully" << std::endl;
    // Respond with success
    res.code = 201; // Created
    res.set_header("Content-Type", "application/json");
    res.write(R"({"message": "User created successfully"})");
    res.end();
  } catch (const std::exception &e) {
    std::cerr << "Error in createUser: " << e.what() << std::endl;
    res.code = 500; // Internal Server Error
    res.set_header("Content-Type", "application/json");
    res.write(R"({"error": "Server error: )" + std::string(e.what()) + R"("})");
    res.end();
  }
}
