cmake_minimum_required(VERSION 3.20) # Specify a recent version of CMake

project(hotel)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(hotel main.cpp user.cpp reservation.cpp room.cpp room_db.cpp hotel_backend.cpp user_db.cpp)

# Include directories for Crow
target_include_directories(hotel PRIVATE /server_utils)

# Link libraries (e.g., Boost)
find_package(Boost REQUIRED)
target_link_libraries(hotel Boost::boost)
