#include <string>

#include "crow_functions.cpp"
#include "hotel_backend.hpp"
#include "room_db.hpp"
#include "server_utils/crow_all.h"
#include "server_utils/sessions.h"
#include "user.hpp"
#include "user_db.hpp"




int main() {
  const std::string kFilename = "data/reservation_records.json";
  HotelBackend backend{kFilename};
  backend.LoadRecordsFromJSONFile();
  auto &user_db = UserDB::instance();

  // Initialize the Crow HTTP server.
  crow::App<crow::CORSHandler> app;

  CROW_ROUTE(app, "/")
  ([&]() {
    try {
      std::string file_path = "html/index.html";
      std::cout << "Serving file: " << file_path << std::endl;
      return crow::response{file_path};
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return crow::response{500,
                            "Internal Server Error: " + std::string(e.what())};
    }
  });

  CROW_ROUTE(app, "/create")
      .methods(crow::HTTPMethod::POST)(createUser);


  app.port(18080).multithreaded().run();
}
