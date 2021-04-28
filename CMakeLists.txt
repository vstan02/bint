cmake_minimum_required(VERSION 3.16)
project(bint)

set(CMAKE_CXX_STANDARD 14)

set(BINT_INCLUDE src/Bint.hpp)
set(BINT_SOURCES src/Bint.cpp)
set(BINT_TESTS src/BintTest.cpp)

add_library(bint ${BINT_SOURCES})
add_executable(test ${BINT_SOURCES} ${BINT_TESTS})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(test PRIVATE GTest::gtest GTest::gtest_main)

install(FILES ${BINT_INCLUDE} DESTINATION include)
install(TARGETS bint ARCHIVE DESTINATION lib)
