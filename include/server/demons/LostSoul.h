#pragma once

#include <random>

#include "server/Demon.h"

namespace DoomMan {
class LostSoul : public Demon {
   public:
    explicit LostSoul(DemonType type, Position startPos)
        : Demon(type, startPos, 600), m_homeBase(startPos), m_gen(std::random_device{}()) {}
    void move(int deltaMs, const GameState& state, const PlayerState& target) override;

   private:
    Position m_homeBase;
    const int AGGRO_RANGE = 6;
    const int PATROL_RADIUS = 4;
    std::mt19937 m_gen;
};

} // namespace DoomMan