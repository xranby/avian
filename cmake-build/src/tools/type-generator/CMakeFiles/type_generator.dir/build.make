# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/dicej/p/avian

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dicej/p/avian/cmake-build

# Include any dependencies generated for this target.
include src/tools/type-generator/CMakeFiles/type_generator.dir/depend.make

# Include the progress variables for this target.
include src/tools/type-generator/CMakeFiles/type_generator.dir/progress.make

# Include the compile flags for this target's objects.
include src/tools/type-generator/CMakeFiles/type_generator.dir/flags.make

src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o: src/tools/type-generator/CMakeFiles/type_generator.dir/flags.make
src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o: ../src/tools/type-generator/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dicej/p/avian/cmake-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o"
	cd /home/dicej/p/avian/cmake-build/src/tools/type-generator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/type_generator.dir/main.cpp.o -c /home/dicej/p/avian/src/tools/type-generator/main.cpp

src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/type_generator.dir/main.cpp.i"
	cd /home/dicej/p/avian/cmake-build/src/tools/type-generator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dicej/p/avian/src/tools/type-generator/main.cpp > CMakeFiles/type_generator.dir/main.cpp.i

src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/type_generator.dir/main.cpp.s"
	cd /home/dicej/p/avian/cmake-build/src/tools/type-generator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dicej/p/avian/src/tools/type-generator/main.cpp -o CMakeFiles/type_generator.dir/main.cpp.s

src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.requires:
.PHONY : src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.requires

src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.provides: src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.requires
	$(MAKE) -f src/tools/type-generator/CMakeFiles/type_generator.dir/build.make src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.provides.build
.PHONY : src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.provides

src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.provides.build: src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o

# Object files for target type_generator
type_generator_OBJECTS = \
"CMakeFiles/type_generator.dir/main.cpp.o"

# External object files for target type_generator
type_generator_EXTERNAL_OBJECTS =

src/tools/type-generator/type_generator: src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o
src/tools/type-generator/type_generator: src/tools/type-generator/CMakeFiles/type_generator.dir/build.make
src/tools/type-generator/type_generator: src/libavian_jvm_finder.a
src/tools/type-generator/type_generator: src/system/libavian_system.a
src/tools/type-generator/type_generator: src/util/libavian_util.a
src/tools/type-generator/type_generator: /usr/lib/x86_64-linux-gnu/libz.so
src/tools/type-generator/type_generator: src/tools/type-generator/CMakeFiles/type_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable type_generator"
	cd /home/dicej/p/avian/cmake-build/src/tools/type-generator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/type_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/tools/type-generator/CMakeFiles/type_generator.dir/build: src/tools/type-generator/type_generator
.PHONY : src/tools/type-generator/CMakeFiles/type_generator.dir/build

src/tools/type-generator/CMakeFiles/type_generator.dir/requires: src/tools/type-generator/CMakeFiles/type_generator.dir/main.cpp.o.requires
.PHONY : src/tools/type-generator/CMakeFiles/type_generator.dir/requires

src/tools/type-generator/CMakeFiles/type_generator.dir/clean:
	cd /home/dicej/p/avian/cmake-build/src/tools/type-generator && $(CMAKE_COMMAND) -P CMakeFiles/type_generator.dir/cmake_clean.cmake
.PHONY : src/tools/type-generator/CMakeFiles/type_generator.dir/clean

src/tools/type-generator/CMakeFiles/type_generator.dir/depend:
	cd /home/dicej/p/avian/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dicej/p/avian /home/dicej/p/avian/src/tools/type-generator /home/dicej/p/avian/cmake-build /home/dicej/p/avian/cmake-build/src/tools/type-generator /home/dicej/p/avian/cmake-build/src/tools/type-generator/CMakeFiles/type_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/tools/type-generator/CMakeFiles/type_generator.dir/depend

