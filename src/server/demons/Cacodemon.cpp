#include "server/demons/Cacodemon.h"

#include <algorithm>
#include <vector>

namespace Doom {

void Cacodemon::move(int deltaMs, const GameState& state, const PlayerState& target) {
    m_timeAccumulator += deltaMs;
    if (m_timeAccumulator < m_moveIntervalMs) return;
    m_timeAccumulator = 0;

    if (m_frightened) return;

    std::vector<Position> allMoves = {{m_pos.x, m_pos.y - 1},
                                      {m_pos.x, m_pos.y + 1},
                                      {m_pos.x - 1, m_pos.y},
                                      {m_pos.x + 1, m_pos.y}};

    std::vector<Position> legalMoves;

    for (int i = 0; i < allMoves.size(); i++) {
        Position p = allMoves[i];

        if (p.x >= 0 && p.x < BOARD_SIZE && p.y >= 0 && p.y < BOARD_SIZE) {
            if (state.board[p.y][p.x] != TileType::Wall) {
                legalMoves.push_back(p);
            }
        }
    }

    if (legalMoves.size() > 0) {
        int randomIndex = rand() % legalMoves.size();
        m_pos = legalMoves[randomIndex];
    }
}
}  // namespace Doom