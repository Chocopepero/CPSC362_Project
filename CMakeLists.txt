cmake_minimum_required(VERSION 3.20)

project(hotel)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(hotel main.cpp user.cpp reservation.cpp room.cpp room_db.cpp hotel_backend.cpp user_db.cpp json_util.cpp)

# Include directories for Crow
target_include_directories(hotel PRIVATE server_utils)

# Specify the Boost root and library directories explicitly
set(BOOST_ROOT "/usr/include/boost")
set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")

# Find Boost (ensure system and ASIO components)
find_package(Boost REQUIRED COMPONENTS system)

# Set the ASIO include directory manually
set(ASIO_INCLUDE_DIR "/usr/include")

# Include ASIO and Boost headers
include_directories(${ASIO_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

# Link Boost libraries
target_link_libraries(hotel ${Boost_LIBRARIES})
