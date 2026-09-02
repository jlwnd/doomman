#pragma once

#include <cstdint>

#include "common/Tiles.h"
#include "common/Types.h"
namespace DoomMan {
/// Sztuczny gracz
class AiPlayer {
   public:
    uint32_t m_playerId;
    PlayerInput decideMove(const GameState& state) const;

   private:
    Position findClosestValuableTarget(const GameState& state, const Position currentPos) const;
    PlayerState findPlayerWithId(const GameState& state, const uint32_t playerId) const;
};
}  // namespace DoomMan