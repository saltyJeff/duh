cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(duh)
add_definitions(-DDESKTOP)

if(${CMAKE_MAJOR_VERSION} EQUAL 2)
    macro(use_cxx11)
        if (CMAKE_VERSION VERSION_LESS "3.1")
            if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
            endif ()
        else ()
            set (CMAKE_CXX_STANDARD 11)
        endif ()
    endmacro(use_cxx11)

    use_cxx11()

    add_executable(duh catch/catch.h main.cpp compat/compat.h src/DuhInput.cpp src/DuhRead.cpp src/DuhRead.h src/checksum.cpp src/checksum.h src/consts.h tests/readTests.cpp tests/writeTests.cpp)
else()
    set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
    add_library(Catch INTERFACE)
    target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
    add_executable(duh main.cpp compat/compat.h src/DuhInput.cpp src/DuhRead.cpp src/DuhRead.h src/checksum.cpp src/checksum.h src/consts.h tests/readTests.cpp tests/writeTests.cpp catch/streq.h)
    target_link_libraries(duh Catch)
endif()

#