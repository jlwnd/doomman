#include "common/Types.h"
#include <iostream>

int main() {
    Doom::GameState game;
    game.mode = Doom::GameMode::Lobby;
    
    std::cout << "Serwer DoomMan Running" << std::endl;
    std::cout << "Board size: " << game.board.size() << "x" << game.board[0].size() << std::endl;
    
    Doom::Position p1{10, 10};
    Doom::Position p2{10, 10};
    if (p1 == p2) {
        std::cout << "Position comparison is working!" << std::endl;
    }

    return 0;
}