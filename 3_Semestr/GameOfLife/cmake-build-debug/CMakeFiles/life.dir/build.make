# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/cristina/clion-2017.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/cristina/clion-2017.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cristina/Prog/life

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cristina/Prog/life/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/life.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/life.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/life.dir/flags.make

CMakeFiles/life.dir/Field.cpp.o: CMakeFiles/life.dir/flags.make
CMakeFiles/life.dir/Field.cpp.o: ../Field.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cristina/Prog/life/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/life.dir/Field.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/life.dir/Field.cpp.o -c /home/cristina/Prog/life/Field.cpp

CMakeFiles/life.dir/Field.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/life.dir/Field.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cristina/Prog/life/Field.cpp > CMakeFiles/life.dir/Field.cpp.i

CMakeFiles/life.dir/Field.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/life.dir/Field.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cristina/Prog/life/Field.cpp -o CMakeFiles/life.dir/Field.cpp.s

CMakeFiles/life.dir/Field.cpp.o.requires:

.PHONY : CMakeFiles/life.dir/Field.cpp.o.requires

CMakeFiles/life.dir/Field.cpp.o.provides: CMakeFiles/life.dir/Field.cpp.o.requires
	$(MAKE) -f CMakeFiles/life.dir/build.make CMakeFiles/life.dir/Field.cpp.o.provides.build
.PHONY : CMakeFiles/life.dir/Field.cpp.o.provides

CMakeFiles/life.dir/Field.cpp.o.provides.build: CMakeFiles/life.dir/Field.cpp.o


# Object files for target life
life_OBJECTS = \
"CMakeFiles/life.dir/Field.cpp.o"

# External object files for target life
life_EXTERNAL_OBJECTS =

life: CMakeFiles/life.dir/Field.cpp.o
life: CMakeFiles/life.dir/build.make
life: CMakeFiles/life.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cristina/Prog/life/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable life"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/life.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/life.dir/build: life

.PHONY : CMakeFiles/life.dir/build

CMakeFiles/life.dir/requires: CMakeFiles/life.dir/Field.cpp.o.requires

.PHONY : CMakeFiles/life.dir/requires

CMakeFiles/life.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/life.dir/cmake_clean.cmake
.PHONY : CMakeFiles/life.dir/clean

CMakeFiles/life.dir/depend:
	cd /home/cristina/Prog/life/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cristina/Prog/life /home/cristina/Prog/life /home/cristina/Prog/life/cmake-build-debug /home/cristina/Prog/life/cmake-build-debug /home/cristina/Prog/life/cmake-build-debug/CMakeFiles/life.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/life.dir/depend

