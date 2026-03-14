cmake_minimum_required(VERSION 3.20)
project(DoomMan)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(include)

add_executable(DoomServer 
    src/GameServer.cpp 
    src/server/MapLoader.cpp
    src/server/GameEngine.cpp
    src/server/NetworkManager.cpp
    include/server/GameEngine.h
    include/server/MapLoader.h
    include/server/NetworkManager.h
    include/common/Types.h
)

target_link_libraries(DoomServer PRIVATE 
    Qt6::Core 
    Qt6::Network
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})