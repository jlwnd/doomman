#pragma once

#include <QDataStream>
#include <cstdint>

namespace DoomMan {

enum class PacketType : uint8_t {
    JoinRequest = 0,
    LobbyUpdate = 1,
    PlayerReady = 2,
    GameStart = 3,
    PlayerInput = 4,
    GameStateSync = 5,
    ChatMessage = 6
};

struct NetworkPacket {
    PacketType type;
};

}  // namespace DoomMan