#pragma once
#include <cstdlib>
#include <vector>

#include "common/Types.h"

namespace DoomMan {
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

    void performRandomFlee(const GameState& state) {
        std::vector<Position> allMoves = {{m_pos.x, m_pos.y - 1},
                                          {m_pos.x, m_pos.y + 1},
                                          {m_pos.x - 1, m_pos.y},
                                          {m_pos.x + 1, m_pos.y}};
        std::vector<Position> legalMoves;
        for (int i = 0; i < allMoves.size(); ++i) {
            Position p = allMoves[i];
            if (p.x >= 0 && p.x < BOARD_SIZE && p.y >= 0 && p.y < BOARD_SIZE) {
                if (!state.board.isWall({p.x, p.y})) {
                    legalMoves.push_back(p);
                }
            }
        }
        if (!legalMoves.empty()) {
            m_pos = legalMoves[rand() % legalMoves.size()];
        }
    }
};
}  // namespace DoomMan