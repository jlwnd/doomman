#pragma once

#include <common/Tiles.h>

#include <array>

namespace DoomMan {
class Map {
   private:
    std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE> m_tiles{};

   public:
    bool isBounds(Position p) const;
    bool isWall(Position p) const;
    TileType at(Position p) const;
    void set(Position p, TileType t);
    const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& tiles() const;
};
}  // namespace DoomMan