#include <iostream>

#include "common/Types.h"
#include "server/MapLoader.h"

int main() {
    auto loadedState = Doom::MapLoader::loadMap("assets/levels/level1.txt");

    if (!loadedState) {
        std::cerr << "Map not imported properly" << std::endl;
        return 1;
    }

    Doom::GameState game = *loadedState;
    std::cout << "Map imported! Size: " << game.board.size() << "x" << game.board[0].size()
              << std::endl;

    if (game.board[0][0] == Doom::TileType::Wall) {
        std::cout << "Found wall at (0,0)" << std::endl;
    }

    return 0;
}