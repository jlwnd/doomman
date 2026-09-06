#include <common/Map.h>

namespace DoomMan {
bool Map::isBounds(Position p) const {
    return m_tiles.inBounds(p.x, p.y);
}

bool Map::isWall(Position p) const {
    return m_tiles.at(p.x, p.y) == TileType::Wall;
}

TileType Map::at(Position p) const {
    return m_tiles.at(p.x, p.y);
}

void Map::set(Position p, TileType t) {
    m_tiles.at(p.x, p.y) = t;
}

const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& Map::tiles() const {
    return m_tiles.rows();
}
}  // namespace DoomMan