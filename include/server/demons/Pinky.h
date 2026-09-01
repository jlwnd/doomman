#pragma once
#include "server/demons/DemonBase.h"

namespace DoomMan {
class Pinky : public DemonBase {
   public:
    explicit Pinky(DemonType type, Position startPos) : DemonBase(type, startPos, 250) {}

    void move(int deltaMs, const GameState& state, const PlayerState& target) override;
};
}  // namespace DoomMan