#pragma once

#include <QDataStream>
#include <array>
#include <compare>
#include <cstdint>
#include <string>
#include <vector>

namespace Doom {

inline constexpr int BOARD_SIZE = 21;
inline constexpr int MAX_PLAYERS = 4;
inline constexpr int DEMON_COUNT = 4;

enum class TileType : uint8_t { Empty, Wall, Corridor, Berserk, SpawnPoint };

enum class DemonType : uint8_t { Imp, Pinky, Cacodemon, LostSoul };

enum class GameMode : uint8_t { Lobby, InGame, Summary };

struct Position {
    int x = 0;
    int y = 0;

    auto operator<=>(const Position&) const = default;
};

struct PlayerState {
    uint32_t id = 0;
    Position pos;
    uint32_t score = 0;
    bool isAlive = true;
    bool hasBerserk = false;
};

struct DemonState {
    DemonType type;
    Position pos;
    bool isFrightened = false;
};

struct GameState {
    GameMode mode = GameMode::Lobby;

    std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE> board;

    std::vector<PlayerState> players;

    std::array<DemonState, DEMON_COUNT> demons;

    int32_t timeLeftSeconds = 180;
};

// Position
inline QDataStream& operator<<(QDataStream& out, const Position& p) {
    return out << p.x << p.y;
}
inline QDataStream& operator>>(QDataStream& in, Position& p) {
    return in >> p.x >> p.y;
}

// PlayerState
inline QDataStream& operator<<(QDataStream& out, const PlayerState& p) {
    return out << p.id << p.pos << p.score << p.isAlive << p.hasBerserk;
}
inline QDataStream& operator>>(QDataStream& in, PlayerState& p) {
    return in >> p.id >> p.pos >> p.score >> p.isAlive >> p.hasBerserk;
}

// DemonState
inline QDataStream& operator<<(QDataStream& out, const DemonState& d) {
    return out << static_cast<uint8_t>(d.type) << d.pos << d.isFrightened;
}
inline QDataStream& operator>>(QDataStream& in, DemonState& d) {
    uint8_t type;
    in >> type >> d.pos >> d.isFrightened;
    d.type = static_cast<DemonType>(type);
    return in;
}

// GameState
inline QDataStream& operator<<(QDataStream& out, const GameState& g) {
    out << static_cast<uint8_t>(g.mode);

    for (const auto& row : g.board) {
        for (const auto& tile : row) {
            out << static_cast<uint8_t>(tile);
        }
    }

    out << static_cast<uint32_t>(g.players.size());
    for (const auto& p : g.players) {
        out << p;
    }

    for (const auto& d : g.demons) {
        out << d;
    }

    out << g.timeLeftSeconds;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, GameState& g) {
    uint8_t mode;
    in >> mode;
    g.mode = static_cast<GameMode>(mode);

    for (auto& row : g.board) {
        for (auto& tile : row) {
            uint8_t t;
            in >> t;
            tile = static_cast<TileType>(t);
        }
    }

    uint32_t playerCount;
    in >> playerCount;
    g.players.clear();
    for (uint32_t i = 0; i < playerCount; ++i) {
        PlayerState p;
        in >> p;
        g.players.push_back(p);
    }

    for (auto& d : g.demons) {
        in >> d;
    }

    in >> g.timeLeftSeconds;
    return in;
}

}  // namespace Doom