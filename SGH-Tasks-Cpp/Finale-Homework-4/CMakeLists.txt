cmake_minimum_required(VERSION 3.10)
project(HW_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{VCPKG_ROOT})
#"-DCMAKE_TOOLCHAIN_FILE=/Users/zakhar/vcpkg/scripts/buildsystems/vcpkg.cmake"
    set(-DCMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    message(STATUS "Using VCPKG toolchain file at $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
    message(FATAL_ERROR "Please define VCPKG_ROOT environment variable pointing to the vcpkg directory")
endif()

include(${-DCMAKE_TOOLCHAIN_FILE})

find_package(Armadillo CONFIG REQUIRED)

find_package(Eigen3 CONFIG REQUIRED)

find_package(QuantLib CONFIG REQUIRED)

find_package(DataFrame CONFIG REQUIRED)

find_package(Matplot++ REQUIRED)

find_package(xlnt REQUIRED)

if(Armadillo_FOUND)
    message(STATUS "Armadillo library found")
else()
    message(FATAL_ERROR "Armadillo library not found")
endif()

#include_directories(${ARMADILLO_INCLUDE_DIR})
#
#link_directories(${ARMADILLO_LIBRARY_DIRS})

add_executable(HW_4 main.cpp)
target_link_libraries(HW_4 PRIVATE armadillo)
target_link_libraries(HW_4 PRIVATE Eigen3::Eigen)
target_link_libraries(HW_4 PRIVATE QuantLib::QuantLib)
target_link_libraries(HW_4 PRIVATE DataFrame::DataFrame)
target_link_libraries(HW_4 PRIVATE xlnt::xlnt)
target_link_libraries(HW_4 PRIVATE Matplot++::cimg  Matplot++::matplot)

message(STATUS "VCPKG_ROOT: $ENV{VCPKG_ROOT}")

#find_package(DataFrame CONFIG REQUIRED)
#target_link_libraries(main PRIVATE DataFrame::DataFrame)


#target_link_libraries(main PRIVATE Eigen3::Eigen)