#pragma once
#include <random>

#include "server/Demon.h"

namespace DoomMan {
class Cacodemon : public Demon {
   public:
    explicit Cacodemon(DemonType type, Position startPos)
        : Demon(type, startPos, 500), m_gen(std::random_device{}()) {}

    void move(int deltaMs, const GameState& state, const PlayerState& target) override;

   private:
    std::mt19937 m_gen;
};
} // namespace DoomMan