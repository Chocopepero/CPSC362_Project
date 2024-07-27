cmake_minimum_required(VERSION 3.20)

project(hotel)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(hotel main.cpp user.cpp reservation.cpp room.cpp room_db.cpp hotel_backend.cpp user_db.cpp)

# Include directories for Crow
target_include_directories(hotel PRIVATE /server_utils)

# Set the Boost root directory if it's not already set in the environment variables
if(NOT DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT "C:/Program Files/boost_1_82_0/boost_1_82_0")
endif()

# Find Boost
find_package(Boost REQUIRED)

# Include the Boost headers
target_include_directories(hotel PRIVATE ${Boost_INCLUDE_DIRS})

# Link Boost libraries
target_link_libraries(hotel Boost::boost)
