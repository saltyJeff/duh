cmake_minimum_required(VERSION 3.13)
project(duh)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DDESKTOP -DDEBUG)

IF(WIN32)
    option(CMAKE_GENERATOR_PLATFORM x86)
    add_definitions(-DPDC_DLL_BUILD)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/windows")
    include_directories("${PROJECT_SOURCE_DIR}/platforms" "${PROJECT_SOURCE_DIR}/include")
ENDIF()
add_executable(duh main.cpp src/DuhSwitch.cpp src/DuhSwitch.h terminal/testHarness.cpp terminal/testHarness.h terminal/LocalSwitch.cpp terminal/LocalSwitch.h terminal/GuiManager.cpp terminal/GuiManager.h include/curses.h compat/compat.h compat/SerialPort.cpp compat/SerialPort.h)
target_link_libraries(duh "pdcurses")
target_link_libraries(duh ${PROJECT_SOURCE_DIR}/platforms/windows/libserialport.dll.a)
target_link_libraries(duh ${PROJECT_SOURCE_DIR}/platforms/windows/libserialport.a)

