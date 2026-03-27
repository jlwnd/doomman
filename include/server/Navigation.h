#pragma once
#include <deque>
#include <vector>

#include "common/Types.h"

namespace DoomMan {
struct Node {
    Position pos;
    int g;
    int h;
    Position parent;

    int f() const {
        return g + h;
    }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

class Navigation {
   public:
    static PlayerInput getNextMoveAStar(
        const Position& start, const Position& target,
        const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& board);

    static int distanceBetween(const Position& a, const Position& b);
};
} // namespace DoomMan