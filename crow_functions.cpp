#include "hotel_backend.hpp"
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
    res.write(R"({"message": "User logged in successfully", "name": ")" + name + R"("})");
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
    std::string name = body["name"].s();
    std::string phone = body["phone"].s();
    int adults = body["adult"].i();
    int children = body["child"].i();
    int number = body["numberOfRooms"].i();
    int arrivemon = body["startMonth"].i();
    int arriveday = body["startDay"].i();
    int arriveyear = body["startYear"].i();
    int depmon = body["endMonth"].i();
    int depday = body["endDay"].i();
    int depyear = body["endYear"].i();
    std::string type = body["room"].s();
    Date arrival{arrivemon,arriveday,arriveyear};
    Date depart{depmon, depday, depyear};

    // Everything's required in HTML.
    // Too tired to validate inputs

    std::pair<bool,int> result = backend.CreateReservation(name, phone, adults, children,
                                             number, arrival, depart, type);
    bool success = result.first;
    std::string id = std::to_string(result.second);

    if (!success) {
      res.code = 500; // Internal Server Error
      res.write("Failed to create reservation");
      res.end();
      return;
    }
    // Respond with success
    res.code = 201; // Logged in
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
