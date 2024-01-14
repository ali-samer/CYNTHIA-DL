# Install script for directory: /Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/AdolcForward"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/AlignedVector3"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/ArpackSupport"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/AutoDiff"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/BVH"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/EulerAngles"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/FFT"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/IterativeSolvers"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/KroneckerProduct"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/LevenbergMarquardt"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/MatrixFunctions"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/MoreVectorization"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/MPRealSupport"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/NonLinearOptimization"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/NumericalDiff"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/OpenGLSupport"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/Polynomials"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/Skyline"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/SparseExtra"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/SpecialFunctions"
    "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-src/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/samer.ali/CLionProjects/CYNTHIA-DL/cmake-build-debug/_deps/eigen-build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

