#pragma once

#include "common/Types.h"
#include "server/Demon.h"

namespace DoomMan {
class DemonBase : public Demon {
   public:
    explicit DemonBase(DemonType type, Position startPos, int speed)
        : m_pos(startPos), m_type(type), m_moveIntervalMs(speed) {}

    Position getPosition() const override;
    DemonType getType() const override;
    bool isFrightened() const override;
    void setFrightened(bool f) override;

   protected:
    Position m_pos;
    DemonType m_type;
    bool m_frightened = false;
    int m_timeAccumulator = 0;
    int m_moveIntervalMs;

    void performRandomFlee(const GameState& state);
};
}  // namespace DoomMan