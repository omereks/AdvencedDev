# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/omer/BIU/AdvencedDev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/omer/BIU/AdvencedDev/build

# Include any dependencies generated for this target.
include CMakeFiles/checkE2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/checkE2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/checkE2.dir/flags.make

CMakeFiles/checkE2.dir/MainTrain.cpp.o: CMakeFiles/checkE2.dir/flags.make
CMakeFiles/checkE2.dir/MainTrain.cpp.o: ../MainTrain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/BIU/AdvencedDev/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/checkE2.dir/MainTrain.cpp.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/checkE2.dir/MainTrain.cpp.o -c /home/omer/BIU/AdvencedDev/MainTrain.cpp

CMakeFiles/checkE2.dir/MainTrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/checkE2.dir/MainTrain.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/BIU/AdvencedDev/MainTrain.cpp > CMakeFiles/checkE2.dir/MainTrain.cpp.i

CMakeFiles/checkE2.dir/MainTrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/checkE2.dir/MainTrain.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/BIU/AdvencedDev/MainTrain.cpp -o CMakeFiles/checkE2.dir/MainTrain.cpp.s

# Object files for target checkE2
checkE2_OBJECTS = \
"CMakeFiles/checkE2.dir/MainTrain.cpp.o"

# External object files for target checkE2
checkE2_EXTERNAL_OBJECTS =

checkE2: CMakeFiles/checkE2.dir/MainTrain.cpp.o
checkE2: CMakeFiles/checkE2.dir/build.make
checkE2: CMakeFiles/checkE2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/omer/BIU/AdvencedDev/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable checkE2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/checkE2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/checkE2.dir/build: checkE2

.PHONY : CMakeFiles/checkE2.dir/build

CMakeFiles/checkE2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/checkE2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/checkE2.dir/clean

CMakeFiles/checkE2.dir/depend:
	cd /home/omer/BIU/AdvencedDev/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/omer/BIU/AdvencedDev /home/omer/BIU/AdvencedDev /home/omer/BIU/AdvencedDev/build /home/omer/BIU/AdvencedDev/build /home/omer/BIU/AdvencedDev/build/CMakeFiles/checkE2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/checkE2.dir/depend
