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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/loksangho/Downloads/bullet3-3.17

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/loksangho/Downloads/bullet3-3.17/build_cmake

# Include any dependencies generated for this target.
include Extras/HACD/CMakeFiles/HACD.dir/depend.make

# Include the progress variables for this target.
include Extras/HACD/CMakeFiles/HACD.dir/progress.make

# Include the compile flags for this target's objects.
include Extras/HACD/CMakeFiles/HACD.dir/flags.make

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o: ../Extras/HACD/hacdGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdGraph.o -c /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdGraph.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdGraph.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdGraph.cpp > CMakeFiles/HACD.dir/hacdGraph.i

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdGraph.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdGraph.cpp -o CMakeFiles/HACD.dir/hacdGraph.s

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o: ../Extras/HACD/hacdHACD.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdHACD.o -c /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdHACD.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdHACD.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdHACD.cpp > CMakeFiles/HACD.dir/hacdHACD.i

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdHACD.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdHACD.cpp -o CMakeFiles/HACD.dir/hacdHACD.s

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o: ../Extras/HACD/hacdICHull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdICHull.o -c /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdICHull.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdICHull.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdICHull.cpp > CMakeFiles/HACD.dir/hacdICHull.i

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdICHull.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdICHull.cpp -o CMakeFiles/HACD.dir/hacdICHull.s

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o: ../Extras/HACD/hacdManifoldMesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdManifoldMesh.o -c /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdManifoldMesh.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdManifoldMesh.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdManifoldMesh.cpp > CMakeFiles/HACD.dir/hacdManifoldMesh.i

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdManifoldMesh.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD/hacdManifoldMesh.cpp -o CMakeFiles/HACD.dir/hacdManifoldMesh.s

# Object files for target HACD
HACD_OBJECTS = \
"CMakeFiles/HACD.dir/hacdGraph.o" \
"CMakeFiles/HACD.dir/hacdHACD.o" \
"CMakeFiles/HACD.dir/hacdICHull.o" \
"CMakeFiles/HACD.dir/hacdManifoldMesh.o"

# External object files for target HACD
HACD_EXTERNAL_OBJECTS =

Extras/HACD/libHACD.3.17.dylib: Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o
Extras/HACD/libHACD.3.17.dylib: Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o
Extras/HACD/libHACD.3.17.dylib: Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o
Extras/HACD/libHACD.3.17.dylib: Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o
Extras/HACD/libHACD.3.17.dylib: Extras/HACD/CMakeFiles/HACD.dir/build.make
Extras/HACD/libHACD.3.17.dylib: Extras/HACD/CMakeFiles/HACD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libHACD.dylib"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HACD.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && $(CMAKE_COMMAND) -E cmake_symlink_library libHACD.3.17.dylib libHACD.3.17.dylib libHACD.dylib

Extras/HACD/libHACD.dylib: Extras/HACD/libHACD.3.17.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate Extras/HACD/libHACD.dylib

# Rule to build all files generated by this target.
Extras/HACD/CMakeFiles/HACD.dir/build: Extras/HACD/libHACD.dylib

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/build

Extras/HACD/CMakeFiles/HACD.dir/clean:
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD && $(CMAKE_COMMAND) -P CMakeFiles/HACD.dir/cmake_clean.cmake
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/clean

Extras/HACD/CMakeFiles/HACD.dir/depend:
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/loksangho/Downloads/bullet3-3.17 /Users/loksangho/Downloads/bullet3-3.17/Extras/HACD /Users/loksangho/Downloads/bullet3-3.17/build_cmake /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD /Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/HACD/CMakeFiles/HACD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/depend

