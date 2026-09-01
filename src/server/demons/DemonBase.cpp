#include "server/demons/DemonBase.h"

#include <cstdlib>
#include <vector>

namespace DoomMan {

Position DemonBase::getPosition() const {
    return m_pos;
}

DemonType DemonBase::getType() const {
    return m_type;
}

bool DemonBase::isFrightened() const {
    return m_frightened;
}

void DemonBase::setFrightened(bool f) {
    m_frightened = f;
}

void DemonBase::performRandomFlee(const GameState& state) {
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
}  // namespace DoomMan