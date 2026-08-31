#pragma once

#include <common/Map.h>

#include <QString>
#include <array>
#include <compare>
#include <cstdint>
#include <string>
#include <vector>

namespace DoomMan {

inline constexpr int MAX_PLAYERS = 4;
inline constexpr int DEMON_COUNT = 4;

enum class DemonType : uint8_t { Imp, Pinky, Cacodemon, LostSoul };

enum class GameMode : uint8_t { Lobby, InGame, Summary };

enum class PlayerInput : uint8_t { MoveUp, MoveDown, MoveLeft, MoveRight, None };

struct PlayerState {
    uint32_t id = 0;
    Position pos;
    PlayerInput lastInput = PlayerInput::None;
    uint32_t score = 0;
    QString name;
    bool isReady = false;
    bool isAlive = true;
    bool hasBerserk = false;
};

struct DemonState {
    DemonType type;
    Position pos;
    bool isFrightened = false;
    bool isAlive = true;
};

struct GameState {
    GameMode mode = GameMode::Lobby;

    Map board;

    std::vector<PlayerState> players;

    std::array<DemonState, DEMON_COUNT> demons;

    int32_t timeLeftSeconds = 180;
};

}  // namespace DoomMan
