#include "server/MapLoader.h"

#include <fstream>
#include <iostream>

namespace DoomMan {

std::optional<GameState> MapLoader::loadMap(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Couldn't open up the map: " << filePath << std::endl;
        return std::nullopt;
    }

    GameState state;
    std::string line;
    int row = 0;

    while (std::getline(file, line) && row < BOARD_SIZE) {
        for (int col = 0; col < BOARD_SIZE && col < (int)line.length(); ++col) {
            state.board[row][col] = charToTile(line[col]);

            if (line[col] == 'P') {
                PlayerState player;
                player.pos = {col, row};
                state.players.push_back(player);
            }
        }
        row++;
    }

    return state;
}

TileType MapLoader::charToTile(char c) {
    switch (c) {
        case '#':
            return TileType::Wall;
        case '.':
            return TileType::Corridor;
        case 'B':
            return TileType::Berserk;
        case 'i':
            return TileType::ImpSpawn;
        case 'p':
            return TileType::PinkySpawn;
        case 'c':
            return TileType::CacodemonSpawn;
        case 'l':
            return TileType::LostSoulSpawn;
        default:
            return TileType::Empty;
    }
}

}  // namespace DoomMan
