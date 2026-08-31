#pragma once

#include <compare>
#include <cstdint>

inline constexpr int BOARD_SIZE = 21;

enum class TileType : uint8_t {
    Empty,
    Wall,
    Corridor,
    Berserk,
    ImpSpawn,
    PinkySpawn,
    CacodemonSpawn,
    LostSoulSpawn
};

struct Position {
    int x = 0;
    int y = 0;

    auto operator<=>(const Position&) const = default;
};