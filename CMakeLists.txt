cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(duh)
add_definitions(-DDESKTOP)
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
set(V2_INCLUDE "")

# Set C++ 11
if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

if(${CMAKE_MAJOR_VERSION} EQUAL 2)
    set(V2_INCLUDE ${CATCH_INCLUDE_DIR} tests/testUtils.h)
endif()

add_executable(duh main.cpp ${V2_INCLUDE} compat/compat.h src/DuhInput.cpp src/DuhRead.cpp src/DuhRead.h src/checksum.cpp src/checksum.h src/consts.h tests/readTests.cpp tests/writeTests.cpp tests/e2eTests.cpp)

if(${CMAKE_MAJOR_VERSION} EQUAL 3)
    add_library(Catch INTERFACE)
    target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
    target_link_libraries(duh Catch)
endif()