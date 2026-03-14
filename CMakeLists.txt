cmake_minimum_required(VERSION 3.20)
project(DoomMan)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(include)

add_executable(DoomServer 
    src/game_server.cpp 
    src/server/map_loader.cpp
)

target_link_libraries(DoomServer PRIVATE Qt6::Widgets Qt6::Network)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})