# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/A3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A3.dir/flags.make

CMakeFiles/A3.dir/main.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A3.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A3.dir/main.cpp.o -c /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/main.cpp

CMakeFiles/A3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/main.cpp > CMakeFiles/A3.dir/main.cpp.i

CMakeFiles/A3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/main.cpp -o CMakeFiles/A3.dir/main.cpp.s

# Object files for target A3
A3_OBJECTS = \
"CMakeFiles/A3.dir/main.cpp.o"

# External object files for target A3
A3_EXTERNAL_OBJECTS =

A3: CMakeFiles/A3.dir/main.cpp.o
A3: CMakeFiles/A3.dir/build.make
A3: src/libstbimage.a
A3: CMakeFiles/A3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable A3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A3.dir/build: A3

.PHONY : CMakeFiles/A3.dir/build

CMakeFiles/A3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A3.dir/clean

CMakeFiles/A3.dir/depend:
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3 /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3 /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/CMakeFiles/A3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A3.dir/depend

