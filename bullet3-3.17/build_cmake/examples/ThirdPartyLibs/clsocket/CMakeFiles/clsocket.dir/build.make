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
include examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/depend.make

# Include the progress variables for this target.
include examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/progress.make

# Include the compile flags for this target's objects.
include examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/flags.make

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/SimpleSocket.o: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/flags.make
examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/SimpleSocket.o: ../examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/SimpleSocket.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clsocket.dir/src/SimpleSocket.o -c /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/SimpleSocket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clsocket.dir/src/SimpleSocket.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp > CMakeFiles/clsocket.dir/src/SimpleSocket.i

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/SimpleSocket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clsocket.dir/src/SimpleSocket.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp -o CMakeFiles/clsocket.dir/src/SimpleSocket.s

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/ActiveSocket.o: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/flags.make
examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/ActiveSocket.o: ../examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/ActiveSocket.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clsocket.dir/src/ActiveSocket.o -c /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/ActiveSocket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clsocket.dir/src/ActiveSocket.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp > CMakeFiles/clsocket.dir/src/ActiveSocket.i

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/ActiveSocket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clsocket.dir/src/ActiveSocket.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp -o CMakeFiles/clsocket.dir/src/ActiveSocket.s

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/PassiveSocket.o: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/flags.make
examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/PassiveSocket.o: ../examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/PassiveSocket.o"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clsocket.dir/src/PassiveSocket.o -c /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/PassiveSocket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clsocket.dir/src/PassiveSocket.i"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp > CMakeFiles/clsocket.dir/src/PassiveSocket.i

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/PassiveSocket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clsocket.dir/src/PassiveSocket.s"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp -o CMakeFiles/clsocket.dir/src/PassiveSocket.s

# Object files for target clsocket
clsocket_OBJECTS = \
"CMakeFiles/clsocket.dir/src/SimpleSocket.o" \
"CMakeFiles/clsocket.dir/src/ActiveSocket.o" \
"CMakeFiles/clsocket.dir/src/PassiveSocket.o"

# External object files for target clsocket
clsocket_EXTERNAL_OBJECTS =

examples/ThirdPartyLibs/clsocket/libclsocket.a: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/SimpleSocket.o
examples/ThirdPartyLibs/clsocket/libclsocket.a: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/ActiveSocket.o
examples/ThirdPartyLibs/clsocket/libclsocket.a: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/src/PassiveSocket.o
examples/ThirdPartyLibs/clsocket/libclsocket.a: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/build.make
examples/ThirdPartyLibs/clsocket/libclsocket.a: examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/loksangho/Downloads/bullet3-3.17/build_cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libclsocket.a"
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && $(CMAKE_COMMAND) -P CMakeFiles/clsocket.dir/cmake_clean_target.cmake
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clsocket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/build: examples/ThirdPartyLibs/clsocket/libclsocket.a

.PHONY : examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/build

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/clean:
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket && $(CMAKE_COMMAND) -P CMakeFiles/clsocket.dir/cmake_clean.cmake
.PHONY : examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/clean

examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/depend:
	cd /Users/loksangho/Downloads/bullet3-3.17/build_cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/loksangho/Downloads/bullet3-3.17 /Users/loksangho/Downloads/bullet3-3.17/examples/ThirdPartyLibs/clsocket /Users/loksangho/Downloads/bullet3-3.17/build_cmake /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket /Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/ThirdPartyLibs/clsocket/CMakeFiles/clsocket.dir/depend

