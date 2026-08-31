#pragma once

#include <QDataStream>

#include "common/Types.h"

namespace DoomMan {
// Position
inline QDataStream& operator<<(QDataStream& out, const Position& p) {
    return out << p.x << p.y;
}
inline QDataStream& operator>>(QDataStream& in, Position& p) {
    return in >> p.x >> p.y;
}

// PlayerState
inline QDataStream& operator<<(QDataStream& out, const PlayerState& p) {
    return out << p.id << p.pos << p.name << p.score << p.isReady << p.isAlive << p.hasBerserk;
}
inline QDataStream& operator>>(QDataStream& in, PlayerState& p) {
    return in >> p.id >> p.pos >> p.name >> p.score >> p.isReady >> p.isAlive >> p.hasBerserk;
}

// DemonState
inline QDataStream& operator<<(QDataStream& out, const DemonState& d) {
    return out << static_cast<uint8_t>(d.type) << d.pos << d.isFrightened << d.isAlive;
}
inline QDataStream& operator>>(QDataStream& in, DemonState& d) {
    uint8_t type;
    in >> type >> d.pos >> d.isFrightened >> d.isAlive;
    d.type = static_cast<DemonType>(type);
    return in;
}

// GameState
inline QDataStream& operator<<(QDataStream& out, const GameState& g) {
    out << static_cast<uint8_t>(g.mode);

    for (const auto& row : g.board.tiles()) {
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

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            uint8_t t;
            in >> t;
            g.board.set({x, y}, static_cast<TileType>(t));
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

// PlayerInput
inline QDataStream& operator<<(QDataStream& out, const PlayerInput& input) {
    return out << static_cast<uint8_t>(input);
}

inline QDataStream& operator>>(QDataStream& in, PlayerInput& input) {
    uint8_t val;
    in >> val;
    input = static_cast<PlayerInput>(val);
    return in;
}

}  // namespace DoomMan