# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/wyt/21_SRML_Referee

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wyt/21_SRML_Referee

# Include any dependencies generated for this target.
include SerialPort/CMakeFiles/SerialPort.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include SerialPort/CMakeFiles/SerialPort.dir/compiler_depend.make

# Include the progress variables for this target.
include SerialPort/CMakeFiles/SerialPort.dir/progress.make

# Include the compile flags for this target's objects.
include SerialPort/CMakeFiles/SerialPort.dir/flags.make

SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.o: SerialPort/CMakeFiles/SerialPort.dir/flags.make
SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.o: SerialPort/SerialPort.cpp
SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.o: SerialPort/CMakeFiles/SerialPort.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyt/21_SRML_Referee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.o"
	cd /home/wyt/21_SRML_Referee/SerialPort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.o -MF CMakeFiles/SerialPort.dir/SerialPort.cpp.o.d -o CMakeFiles/SerialPort.dir/SerialPort.cpp.o -c /home/wyt/21_SRML_Referee/SerialPort/SerialPort.cpp

SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SerialPort.dir/SerialPort.cpp.i"
	cd /home/wyt/21_SRML_Referee/SerialPort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wyt/21_SRML_Referee/SerialPort/SerialPort.cpp > CMakeFiles/SerialPort.dir/SerialPort.cpp.i

SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SerialPort.dir/SerialPort.cpp.s"
	cd /home/wyt/21_SRML_Referee/SerialPort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wyt/21_SRML_Referee/SerialPort/SerialPort.cpp -o CMakeFiles/SerialPort.dir/SerialPort.cpp.s

# Object files for target SerialPort
SerialPort_OBJECTS = \
"CMakeFiles/SerialPort.dir/SerialPort.cpp.o"

# External object files for target SerialPort
SerialPort_EXTERNAL_OBJECTS =

SerialPort/libSerialPort.a: SerialPort/CMakeFiles/SerialPort.dir/SerialPort.cpp.o
SerialPort/libSerialPort.a: SerialPort/CMakeFiles/SerialPort.dir/build.make
SerialPort/libSerialPort.a: SerialPort/CMakeFiles/SerialPort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wyt/21_SRML_Referee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libSerialPort.a"
	cd /home/wyt/21_SRML_Referee/SerialPort && $(CMAKE_COMMAND) -P CMakeFiles/SerialPort.dir/cmake_clean_target.cmake
	cd /home/wyt/21_SRML_Referee/SerialPort && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SerialPort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SerialPort/CMakeFiles/SerialPort.dir/build: SerialPort/libSerialPort.a
.PHONY : SerialPort/CMakeFiles/SerialPort.dir/build

SerialPort/CMakeFiles/SerialPort.dir/clean:
	cd /home/wyt/21_SRML_Referee/SerialPort && $(CMAKE_COMMAND) -P CMakeFiles/SerialPort.dir/cmake_clean.cmake
.PHONY : SerialPort/CMakeFiles/SerialPort.dir/clean

SerialPort/CMakeFiles/SerialPort.dir/depend:
	cd /home/wyt/21_SRML_Referee && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wyt/21_SRML_Referee /home/wyt/21_SRML_Referee/SerialPort /home/wyt/21_SRML_Referee /home/wyt/21_SRML_Referee/SerialPort /home/wyt/21_SRML_Referee/SerialPort/CMakeFiles/SerialPort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SerialPort/CMakeFiles/SerialPort.dir/depend

