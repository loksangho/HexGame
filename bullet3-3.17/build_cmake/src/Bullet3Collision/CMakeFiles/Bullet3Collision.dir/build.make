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
include src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/depend.make

# Include the progress variables for this target.
include src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/progress.make

# Include the compile flags for this target's objects.
include src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/flags.make

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.o: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/flags.make
src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.o: ../src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.o -c /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvh.cpp

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvh.cpp > CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.i

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvh.cpp -o CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.s

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.o: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/flags.make
src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.o: ../src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.o -c /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.cpp

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.cpp > CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.i

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.cpp -o CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.s

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.o: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/flags.make
src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.o: ../src/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.o -c /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.cpp

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.cpp > CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.i

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.cpp -o CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.s

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.o: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/flags.make
src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.o: ../src/Bullet3Collision/NarrowPhaseCollision/b3ConvexUtility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.o -c /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/NarrowPhaseCollision/b3ConvexUtility.cpp

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/NarrowPhaseCollision/b3ConvexUtility.cpp > CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.i

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/NarrowPhaseCollision/b3ConvexUtility.cpp -o CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.s

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.o: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/flags.make
src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.o: ../src/Bullet3Collision/NarrowPhaseCollision/b3CpuNarrowPhase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.o -c /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/NarrowPhaseCollision/b3CpuNarrowPhase.cpp

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/NarrowPhaseCollision/b3CpuNarrowPhase.cpp > CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.i

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision/NarrowPhaseCollision/b3CpuNarrowPhase.cpp -o CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.s

# Object files for target Bullet3Collision
Bullet3Collision_OBJECTS = \
"CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.o" \
"CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.o" \
"CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.o" \
"CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.o" \
"CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.o"

# External object files for target Bullet3Collision
Bullet3Collision_EXTERNAL_OBJECTS =

src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvh.o
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3DynamicBvhBroadphase.o
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/BroadPhaseCollision/b3OverlappingPairCache.o
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3ConvexUtility.o
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/NarrowPhaseCollision/b3CpuNarrowPhase.o
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/build.make
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Geometry/libBullet3Geometry.3.17.dylib
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Common/libBullet3Common.3.17.dylib
src/Bullet3Collision/libBullet3Collision.3.17.dylib: src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library libBullet3Collision.dylib"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Bullet3Collision.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && $(CMAKE_COMMAND) -E cmake_symlink_library libBullet3Collision.3.17.dylib libBullet3Collision.3.17.dylib libBullet3Collision.dylib

src/Bullet3Collision/libBullet3Collision.dylib: src/Bullet3Collision/libBullet3Collision.3.17.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate src/Bullet3Collision/libBullet3Collision.dylib

# Rule to build all files generated by this target.
src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/build: src/Bullet3Collision/libBullet3Collision.dylib

.PHONY : src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/build

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/clean:
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision && $(CMAKE_COMMAND) -P CMakeFiles/Bullet3Collision.dir/cmake_clean.cmake
.PHONY : src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/clean

src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/depend:
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/loksangho/Downloads/bullet3-3.17 /Users/loksangho/Downloads/bullet3-3.17/src/Bullet3Collision /Users/loksangho/Downloads/bullet3-3.17/build_cmake /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision /Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Bullet3Collision/CMakeFiles/Bullet3Collision.dir/depend
