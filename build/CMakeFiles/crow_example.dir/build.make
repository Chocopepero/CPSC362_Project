# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sam/CPSC362/CPSC362_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sam/CPSC362/CPSC362_Project/build

# Include any dependencies generated for this target.
include CMakeFiles/crow_example.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/crow_example.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/crow_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crow_example.dir/flags.make

CMakeFiles/crow_example.dir/main.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/main.cpp.o: ../main.cpp
CMakeFiles/crow_example.dir/main.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crow_example.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/main.cpp.o -MF CMakeFiles/crow_example.dir/main.cpp.o.d -o CMakeFiles/crow_example.dir/main.cpp.o -c /home/sam/CPSC362/CPSC362_Project/main.cpp

CMakeFiles/crow_example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/main.cpp > CMakeFiles/crow_example.dir/main.cpp.i

CMakeFiles/crow_example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/main.cpp -o CMakeFiles/crow_example.dir/main.cpp.s

CMakeFiles/crow_example.dir/user.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/user.cpp.o: ../user.cpp
CMakeFiles/crow_example.dir/user.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/crow_example.dir/user.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/user.cpp.o -MF CMakeFiles/crow_example.dir/user.cpp.o.d -o CMakeFiles/crow_example.dir/user.cpp.o -c /home/sam/CPSC362/CPSC362_Project/user.cpp

CMakeFiles/crow_example.dir/user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/user.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/user.cpp > CMakeFiles/crow_example.dir/user.cpp.i

CMakeFiles/crow_example.dir/user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/user.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/user.cpp -o CMakeFiles/crow_example.dir/user.cpp.s

CMakeFiles/crow_example.dir/reservation.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/reservation.cpp.o: ../reservation.cpp
CMakeFiles/crow_example.dir/reservation.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/crow_example.dir/reservation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/reservation.cpp.o -MF CMakeFiles/crow_example.dir/reservation.cpp.o.d -o CMakeFiles/crow_example.dir/reservation.cpp.o -c /home/sam/CPSC362/CPSC362_Project/reservation.cpp

CMakeFiles/crow_example.dir/reservation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/reservation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/reservation.cpp > CMakeFiles/crow_example.dir/reservation.cpp.i

CMakeFiles/crow_example.dir/reservation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/reservation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/reservation.cpp -o CMakeFiles/crow_example.dir/reservation.cpp.s

CMakeFiles/crow_example.dir/room.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/room.cpp.o: ../room.cpp
CMakeFiles/crow_example.dir/room.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/crow_example.dir/room.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/room.cpp.o -MF CMakeFiles/crow_example.dir/room.cpp.o.d -o CMakeFiles/crow_example.dir/room.cpp.o -c /home/sam/CPSC362/CPSC362_Project/room.cpp

CMakeFiles/crow_example.dir/room.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/room.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/room.cpp > CMakeFiles/crow_example.dir/room.cpp.i

CMakeFiles/crow_example.dir/room.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/room.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/room.cpp -o CMakeFiles/crow_example.dir/room.cpp.s

CMakeFiles/crow_example.dir/room_db.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/room_db.cpp.o: ../room_db.cpp
CMakeFiles/crow_example.dir/room_db.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/crow_example.dir/room_db.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/room_db.cpp.o -MF CMakeFiles/crow_example.dir/room_db.cpp.o.d -o CMakeFiles/crow_example.dir/room_db.cpp.o -c /home/sam/CPSC362/CPSC362_Project/room_db.cpp

CMakeFiles/crow_example.dir/room_db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/room_db.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/room_db.cpp > CMakeFiles/crow_example.dir/room_db.cpp.i

CMakeFiles/crow_example.dir/room_db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/room_db.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/room_db.cpp -o CMakeFiles/crow_example.dir/room_db.cpp.s

CMakeFiles/crow_example.dir/hotel_backend.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/hotel_backend.cpp.o: ../hotel_backend.cpp
CMakeFiles/crow_example.dir/hotel_backend.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/crow_example.dir/hotel_backend.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/hotel_backend.cpp.o -MF CMakeFiles/crow_example.dir/hotel_backend.cpp.o.d -o CMakeFiles/crow_example.dir/hotel_backend.cpp.o -c /home/sam/CPSC362/CPSC362_Project/hotel_backend.cpp

CMakeFiles/crow_example.dir/hotel_backend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/hotel_backend.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/hotel_backend.cpp > CMakeFiles/crow_example.dir/hotel_backend.cpp.i

CMakeFiles/crow_example.dir/hotel_backend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/hotel_backend.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/hotel_backend.cpp -o CMakeFiles/crow_example.dir/hotel_backend.cpp.s

CMakeFiles/crow_example.dir/user_db.cpp.o: CMakeFiles/crow_example.dir/flags.make
CMakeFiles/crow_example.dir/user_db.cpp.o: ../user_db.cpp
CMakeFiles/crow_example.dir/user_db.cpp.o: CMakeFiles/crow_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/crow_example.dir/user_db.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crow_example.dir/user_db.cpp.o -MF CMakeFiles/crow_example.dir/user_db.cpp.o.d -o CMakeFiles/crow_example.dir/user_db.cpp.o -c /home/sam/CPSC362/CPSC362_Project/user_db.cpp

CMakeFiles/crow_example.dir/user_db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_example.dir/user_db.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sam/CPSC362/CPSC362_Project/user_db.cpp > CMakeFiles/crow_example.dir/user_db.cpp.i

CMakeFiles/crow_example.dir/user_db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_example.dir/user_db.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sam/CPSC362/CPSC362_Project/user_db.cpp -o CMakeFiles/crow_example.dir/user_db.cpp.s

# Object files for target crow_example
crow_example_OBJECTS = \
"CMakeFiles/crow_example.dir/main.cpp.o" \
"CMakeFiles/crow_example.dir/user.cpp.o" \
"CMakeFiles/crow_example.dir/reservation.cpp.o" \
"CMakeFiles/crow_example.dir/room.cpp.o" \
"CMakeFiles/crow_example.dir/room_db.cpp.o" \
"CMakeFiles/crow_example.dir/hotel_backend.cpp.o" \
"CMakeFiles/crow_example.dir/user_db.cpp.o"

# External object files for target crow_example
crow_example_EXTERNAL_OBJECTS =

crow_example: CMakeFiles/crow_example.dir/main.cpp.o
crow_example: CMakeFiles/crow_example.dir/user.cpp.o
crow_example: CMakeFiles/crow_example.dir/reservation.cpp.o
crow_example: CMakeFiles/crow_example.dir/room.cpp.o
crow_example: CMakeFiles/crow_example.dir/room_db.cpp.o
crow_example: CMakeFiles/crow_example.dir/hotel_backend.cpp.o
crow_example: CMakeFiles/crow_example.dir/user_db.cpp.o
crow_example: CMakeFiles/crow_example.dir/build.make
crow_example: CMakeFiles/crow_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sam/CPSC362/CPSC362_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable crow_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crow_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crow_example.dir/build: crow_example
.PHONY : CMakeFiles/crow_example.dir/build

CMakeFiles/crow_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crow_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crow_example.dir/clean

CMakeFiles/crow_example.dir/depend:
	cd /home/sam/CPSC362/CPSC362_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sam/CPSC362/CPSC362_Project /home/sam/CPSC362/CPSC362_Project /home/sam/CPSC362/CPSC362_Project/build /home/sam/CPSC362/CPSC362_Project/build /home/sam/CPSC362/CPSC362_Project/build/CMakeFiles/crow_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crow_example.dir/depend

