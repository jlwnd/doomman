cmake_minimum_required(VERSION 3.20)
project(DoomMan)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

include_directories(include)

# SERVER
add_executable(DoomServer 
    src/GameServer.cpp 
    src/server/MapLoader.cpp
    src/server/GameEngine.cpp
    src/server/NetworkManager.cpp
    include/server/GameEngine.h
    include/server/NetworkManager.h
    include/common/Types.h
    include/common/Serialization.h
)
target_link_libraries(DoomServer PRIVATE Qt6::Network Qt6::Core)

# CLIENT
add_executable(DoomClient
    src/GameClient.cpp
    src/client/NetworkManager.cpp
    src/client/GameWidget.cpp
    include/client/NetworkManager.h
    include/client/GameWidget.h
    include/common/Types.h
    include/common/Serialization.h
)
target_link_libraries(DoomClient PRIVATE Qt6::Widgets Qt6::Network)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})