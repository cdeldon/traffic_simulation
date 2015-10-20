cmake_minimum_required(VERSION 2.8)
project(traffic_simulation)

IF(MSVC) 
    
ELSE(MSVC)
    SET(CMAKE_CXX_FLAGS "-std=c++11")
ENDIF(MSVC)

include_directories(include)

# add all cpp files as SOURCES
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

set(EXECUTABLE_OUTPUT_PATH "./bin/")
add_executable(traffic_simulation ${SOURCES} ${HEADERS})