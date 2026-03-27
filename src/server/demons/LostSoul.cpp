#include "server/demons/LostSoul.h"

#include <vector>

#include "server/Navigation.h"

namespace DoomMan {
void LostSoul::move(int deltaMs, const GameState& state, const PlayerState& target) {
    m_timeAccumulator += deltaMs;
    int currentInterval = m_frightened ? m_moveIntervalMs * 2 : m_moveIntervalMs;
    if (m_timeAccumulator < currentInterval) {
        return;
    }
    m_timeAccumulator = 0;

    if (m_frightened) {
        performRandomFlee(state);
        return;
    }

    int distToPlayer = Navigation::distanceBetween(m_pos, target.pos);

    if (distToPlayer <= AGGRO_RANGE) {
        PlayerInput nextStep = Navigation::getNextMoveAStar(m_pos, target.pos, state.board);

        int dx = 0, dy = 0;
        if (nextStep == PlayerInput::MoveUp)
            dy = -1;
        else if (nextStep == PlayerInput::MoveDown)
            dy = 1;
        else if (nextStep == PlayerInput::MoveLeft)
            dx = -1;
        else if (nextStep == PlayerInput::MoveRight)
            dx = 1;

        if (state.board[m_pos.y + dy][m_pos.x + dx] != TileType::Wall) {
            m_pos.x += dx;
            m_pos.y += dy;
        }
    } else {
        int currentDistHome = Navigation::distanceBetween(m_pos, m_homeBase);
        if (currentDistHome > PATROL_RADIUS) {
            PlayerInput nextStep = Navigation::getNextMoveAStar(m_pos, m_homeBase, state.board);

            int dx = 0, dy = 0;
            if (nextStep == PlayerInput::MoveUp)
                dy = -1;
            else if (nextStep == PlayerInput::MoveDown)
                dy = 1;
            else if (nextStep == PlayerInput::MoveLeft)
                dx = -1;
            else if (nextStep == PlayerInput::MoveRight)
                dx = 1;

            if (state.board[m_pos.y + dy][m_pos.x + dx] != TileType::Wall) {
                m_pos.x += dx;
                m_pos.y += dy;
            }
        } else {
            std::vector<Position> allMoves = {{m_pos.x, m_pos.y - 1},
                                              {m_pos.x, m_pos.y + 1},
                                              {m_pos.x - 1, m_pos.y},
                                              {m_pos.x + 1, m_pos.y}};

            std::vector<Position> legalMoves;
            for (int i = 0; i < allMoves.size(); i++) {
                Position p = allMoves[i];

                if (p.x >= 0 && p.x < BOARD_SIZE && p.y >= 0 && p.y < BOARD_SIZE) {
                    if (state.board[p.y][p.x] != TileType::Wall) {
                        int distFromHome = Navigation::distanceBetween(p, m_homeBase);
                        if (distFromHome <= PATROL_RADIUS) {
                            legalMoves.push_back(p);
                        }
                    }
                }
            }

            if (!legalMoves.empty()) {
                std::uniform_int_distribution<size_t> dist(0, legalMoves.size() - 1);
                m_pos = legalMoves[dist(m_gen)];
            }
        }
    }
}
} // namespace DoomMan
