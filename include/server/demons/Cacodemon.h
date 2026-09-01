#pragma once
#include <random>

#include "server/demons/DemonBase.h"

namespace DoomMan {
class Cacodemon : public DemonBase {
   public:
    explicit Cacodemon(DemonType type, Position startPos)
        : DemonBase(type, startPos, 500), m_gen(std::random_device{}()) {}

    void move(int deltaMs, const GameState& state, const PlayerState& target) override;

   private:
    std::mt19937 m_gen;
};
}  // namespace DoomMan