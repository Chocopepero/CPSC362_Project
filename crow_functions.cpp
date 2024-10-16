#include "hotel_backend.hpp"
#include "json_util.hpp"
#include "server_utils/crow_all.h"
#include "user_db.hpp"

void createUser(const crow::request &req, crow::response &res) {
  auto &user_db = UserDB::instance();
  try {
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

void loginUser(const crow::request &req, crow::response &res) {
  auto &user_db = UserDB::instance();
  try {
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

    // Validate input
    if (username.empty() || password.empty()) {
      res.code = 400; // Bad Request
      res.write("Missing required fields");
      res.end();
      return;
    }

    // Log-in User
    std::string name;
    bool success = user_db.verify_login(username, password);
    if (!success) {
      res.code = 401; // Unauthorized
      res.write("Invalid username or password");
      res.end();
      return;
    }

    // Respond with success
    res.code = 200; // OK
    res.set_header("Content-Type", "application/json");
    res.write(R"({"message": "User logged in successfully", "name": ")" + name +
              R"("})");
    res.end();
  } catch (const std::exception &e) {
    std::cerr << "Error in loginUser: " << e.what() << std::endl;
    res.code = 500; // Internal Server Error
    res.set_header("Content-Type", "application/json");
    res.write(R"({"error": "Server error: )" + std::string(e.what()) + R"("})");
    res.end();
  }
}

void createReservation(const crow::request &req, crow::response &res,
                       HotelBackend &backend) {
  try {
    // Parse JSON request body
    auto body = crow::json::load(req.body);
    if (!body) {
      res.code = 400; // Bad Request
      res.write("Invalid JSON format");
      res.end();
      return;
    }

    // Extract user details from JSON
    Date arrivalDate{body["arrivalDate"].s()};
    Date departureDate{body["departureDate"].s()};
    std::string name = body["name"].s();
    int adults = body["numAdults"].i();
    int children = body["numChildren"].i();
    int number = body["numberRooms"].i();
    std::string phone = body["phone"].s();
    std::string type = body["roomType"].s();

    // Everything's required in HTML.
    // Too tired to validate inputs

    std::pair<bool, int> result =
        backend.CreateReservation(name, phone, adults, children, number,
                                  arrivalDate, departureDate, type);
    bool success = result.first;
    std::string id = std::to_string(result.second);

    if (!success) {
      res.code = 500; // Internal Server Error
      res.write("Failed to create reservation");
      res.end();
      return;
    }
    // Respond with success
    res.code = 201; // Reservation Success
    res.set_header("Content-Type", "application/json");
    res.write("{"
              "\"message\": \"Reservation created successfully!\","
              "\"reservation_id\": \"" +
              id +
              "\""
              "}");
    res.end();
  } catch (const std::exception &e) {
    std::cerr << "Error in createReservation: " << e.what() << std::endl;
    res.code = 500; // Internal Server Error
    res.set_header("Content-Type", "application/json");
    res.write(R"({"error": "Server error: )" + std::string(e.what()) + R"("})");
    res.end();
  }
}
