#pragma once
#include "server/Demon.h"

namespace Doom {
class Imp : public Demon {
    using Demon::Demon;

    void move(const GameState& state, const PlayerState& target) override;
};
}  // namespace Doom