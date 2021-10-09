cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME ParkHW1)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDART_REQURED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCE_FILES roman_to_arabic.c)
add_library(roman_to_arabic STATIC ${LIB_SOURCE_FILES})

add_executable(main main.c)
target_link_libraries(main roman_to_arabic)

add_subdirectory(./gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(rta_test rta_test.cpp)
target_link_libraries(rta_test ${GTEST_LIBRARIES} pthread roman_to_arabic)