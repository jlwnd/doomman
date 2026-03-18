#pragma once
#include "common/Types.h"

namespace Doom {
class Demon {
   public:
    explicit Demon(DemonType type, Position startPos, int speed)
        : m_pos(startPos), m_type(type), m_moveIntervalMs(speed) {}
    virtual ~Demon() = default;

    virtual void move(int deltaMs, const GameState& state, const PlayerState& target) = 0;

    Position getPosition() const {
        return m_pos;
    }
    DemonType getType() const {
        return m_type;
    }
    bool isFrightened() const {
        return m_frightened;
    }
    void setFrightened(bool f) {
        m_frightened = f;
    }

   protected:
    Position m_pos;
    DemonType m_type;
    bool m_frightened = false;
    int m_timeAccumulator = 0;
    int m_moveIntervalMs;
};
}  // namespace Doom