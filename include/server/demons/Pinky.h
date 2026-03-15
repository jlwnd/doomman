#pragma once
#include "server/Demon.h"

namespace Doom {
class Pinky : public Demon {
   public:
    explicit Pinky(DemonType type, Position startPos) : Demon(type, startPos, 250) {}

    void move(int deltaMs, const GameState& state, const PlayerState& target) override;
};
}  // namespace Doom