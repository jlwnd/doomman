#include <common/Map.h>

namespace DoomMan {
bool Map::isBounds(Position p) const {
    return p.x >= 0 && p.x < BOARD_SIZE && p.y >= 0 && p.y < BOARD_SIZE;
}

bool Map::isWall(Position p) const {
    return m_tiles[p.y][p.x] == TileType::Wall;
}

TileType Map::at(Position p) const {
    return m_tiles[p.y][p.x];
}

void Map::set(Position p, TileType t) {
    m_tiles[p.y][p.x] = t;
}

const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& Map::tiles() const {
    return m_tiles;
}
}  // namespace DoomMan