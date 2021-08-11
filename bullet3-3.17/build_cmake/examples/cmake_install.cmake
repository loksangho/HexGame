# Install script for directory: /Users/loksangho/Downloads/bullet3-3.17/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/HelloWorld/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/BasicDemo/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ExampleBrowser/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/RobotSimulator/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/SharedMemory/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/Gwen/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/BussIK/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/clsocket/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/OpenGLWindow/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/TwoJoint/cmake_install.cmake")
  include("/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/pybullet/cmake_install.cmake")

endif()

