cmake_minimum_required(VERSION 3.20)
project(DoomMan)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

include_directories(include)

# SERVER
add_executable(DoomManServer 
    src/GameServer.cpp 
    src/server/MapLoader.cpp
    src/server/Map.cpp
    src/server/GameEngine.cpp
    src/server/GameEngineDriver.cpp
    src/server/ServerNetworkManager.cpp
    src/server/Navigation.cpp
    src/server/AiPlayer.cpp
    src/server/demons/DemonBase.cpp
    src/server/demons/Imp.cpp
    src/server/demons/Pinky.cpp
    src/server/demons/Cacodemon.cpp
    src/server/demons/LostSoul.cpp
    src/server/demons/DemonSpawner.cpp
    src/server/GameServerHost.cpp
    include/server/AiPlayer.h
    include/server/GameEngine.h
    include/server/GameEngineDriver.h
    include/server/ServerNetworkManager.h
    include/server/Demon.h
    include/server/demons/DemonBase.h
    include/server/demons/Imp.h
    include/server/demons/Pinky.h
    include/server/demons/Cacodemon.h
    include/server/demons/LostSoul.h
    include/server/demons/DemonSpawner.h
    include/server/GameServerHost.h
    include/server/Navigation.h
    include/common/Types.h
    include/common/Serialization.h
    include/common/Protocol.h
    include/common/Tiles.h
    include/common/Map.h
)
target_link_libraries(DoomManServer PRIVATE Qt6::Network Qt6::Core)

# CLIENT
add_executable(DoomManClient
    src/GameClient.cpp
    src/client/NetworkManager.cpp
    src/client/GameWidget.cpp
    src/client/MainWindow.cpp
    src/client/MainMenuWidget.cpp
    src/server/GameServerHost.cpp
    src/server/GameEngineDriver.cpp
    src/server/GameEngine.cpp
    src/server/MapLoader.cpp
    src/server/Map.cpp
    src/server/ServerNetworkManager.cpp
    src/server/Navigation.cpp
    src/server/AiPlayer.cpp
    src/server/demons/DemonBase.cpp
    src/server/demons/Imp.cpp
    src/server/demons/Pinky.cpp
    src/server/demons/Cacodemon.cpp
    src/server/demons/LostSoul.cpp
    src/server/demons/DemonSpawner.cpp

    include/client/NetworkManager.h
    include/client/GameWidget.h
    include/client/MainWindow.h
    include/client/MainMenuWidget.h
    include/server/GameServerHost.h
    include/server/GameEngine.h
    include/server/GameEngineDriver.h
    include/server/ServerNetworkManager.h
    include/common/Types.h
    include/common/Serialization.h
    include/common/Protocol.h
    include/common/Tiles.h
    include/common/Map.h
)
target_link_libraries(DoomManClient PRIVATE Qt6::Widgets Qt6::Network)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_executable(test_grid tests/test_grid.cpp)
add_test(NAME test_grid COMMAND test_grid)

add_executable(test_aiplayer
    tests/test_aiplayer.cpp
    src/server/AiPlayer.cpp
    src/server/Navigation.cpp
    src/server/Map.cpp
)
target_link_libraries(test_aiplayer PRIVATE Qt6::Core)
add_test(NAME test_aiplayer COMMAND test_aiplayer)