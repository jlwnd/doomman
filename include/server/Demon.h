#pragma once

#include "common/Types.h"

namespace DoomMan {
class Demon {
   public:
    virtual ~Demon() = default;

    virtual void move(int deltaMs, const GameState& state, const PlayerState& target) = 0;
    virtual Position getPosition() const = 0;
    virtual DemonType getType() const = 0;
    virtual bool isFrightened() const = 0;
    virtual void setFrightened(bool f) = 0;
};
}  // namespace DoomMan