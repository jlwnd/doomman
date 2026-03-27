#pragma once
#include "server/Demon.h"

namespace DoomMan {
class Imp : public Demon {
   public:
    explicit Imp(DemonType type, Position startPos) : Demon(type, startPos, 400) {}

    void move(int deltaMs, const GameState& state, const PlayerState& target) override;
};
} // namespace DoomMan