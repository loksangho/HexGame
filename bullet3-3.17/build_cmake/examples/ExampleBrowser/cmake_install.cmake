# Install script for directory: /Users/loksangho/Downloads/bullet3-3.17/examples/ExampleBrowser

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ExampleBrowser/libBulletExampleBrowserLib.3.17.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletSoftBody"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/InverseDynamics"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletInverseDynamics"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/OpenGLWindow"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/Gwen"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/BussIK"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletDynamics"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletCollision"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/LinearMath"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Common"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.3.17.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ExampleBrowser/libBulletExampleBrowserLib.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletSoftBody"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/Extras/InverseDynamics"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletInverseDynamics"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/OpenGLWindow"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/Gwen"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/examples/ThirdPartyLibs/BussIK"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletDynamics"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/BulletCollision"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/LinearMath"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/loksangho/Downloads/bullet3-3.17/build_cmake/src/Bullet3Common"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libBulletExampleBrowserLib.dylib")
    endif()
  endif()
endif()

