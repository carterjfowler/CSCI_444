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
include src/CMakeFiles/stbimage.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/stbimage.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/stbimage.dir/flags.make

src/CMakeFiles/stbimage.dir/stbimage.cpp.o: src/CMakeFiles/stbimage.dir/flags.make
src/CMakeFiles/stbimage.dir/stbimage.cpp.o: ../src/stbimage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/stbimage.dir/stbimage.cpp.o"
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stbimage.dir/stbimage.cpp.o -c /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/src/stbimage.cpp

src/CMakeFiles/stbimage.dir/stbimage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stbimage.dir/stbimage.cpp.i"
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/src/stbimage.cpp > CMakeFiles/stbimage.dir/stbimage.cpp.i

src/CMakeFiles/stbimage.dir/stbimage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stbimage.dir/stbimage.cpp.s"
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/src/stbimage.cpp -o CMakeFiles/stbimage.dir/stbimage.cpp.s

# Object files for target stbimage
stbimage_OBJECTS = \
"CMakeFiles/stbimage.dir/stbimage.cpp.o"

# External object files for target stbimage
stbimage_EXTERNAL_OBJECTS =

src/libstbimage.a: src/CMakeFiles/stbimage.dir/stbimage.cpp.o
src/libstbimage.a: src/CMakeFiles/stbimage.dir/build.make
src/libstbimage.a: src/CMakeFiles/stbimage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstbimage.a"
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/stbimage.dir/cmake_clean_target.cmake
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stbimage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/stbimage.dir/build: src/libstbimage.a

.PHONY : src/CMakeFiles/stbimage.dir/build

src/CMakeFiles/stbimage.dir/clean:
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/stbimage.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/stbimage.dir/clean

src/CMakeFiles/stbimage.dir/depend:
	cd /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3 /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/src /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src /Users/carterfowler/Desktop/Comp_Sci/444/Projects/A3/cmake-build-debug/src/CMakeFiles/stbimage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/stbimage.dir/depend

