#pragma once
#include "server/demons/DemonBase.h"

namespace DoomMan {
class Imp : public DemonBase {
   public:
    explicit Imp(DemonType type, Position startPos) : DemonBase(type, startPos, 400) {}

    void move(int deltaMs, const GameState& state, const PlayerState& target) override;
};
}  // namespace DoomMan