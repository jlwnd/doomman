#include "server/demons/Pinky.h"

#include <algorithm>

#include "server/Navigation.h"

namespace DoomMan {
void Pinky::move(int deltaMs, const GameState& state, const PlayerState& target) {
    m_timeAccumulator += deltaMs;
    int currentInterval = m_frightened ? m_moveIntervalMs * 2 : m_moveIntervalMs;

    if (m_timeAccumulator < currentInterval) return;
    m_timeAccumulator = 0;

    if (m_frightened) {
        performRandomFlee(state);
        return;
    }

    Position finalTarget;

    finalTarget = target.pos;
    int offset = 4;

    switch (target.lastInput) {
        case PlayerInput::MoveUp:
            finalTarget.y -= offset;
            break;
        case PlayerInput::MoveDown:
            finalTarget.y += offset;
            break;
        case PlayerInput::MoveLeft:
            finalTarget.x -= offset;
            break;
        case PlayerInput::MoveRight:
            finalTarget.x += offset;
            break;
        default:
            break;
    }

    finalTarget.x = std::clamp(finalTarget.x, 1, BOARD_SIZE - 2);
    finalTarget.y = std::clamp(finalTarget.y, 1, BOARD_SIZE - 2);

    PlayerInput step = Navigation::getNextMoveAStar(m_pos, finalTarget, state.board);

    int dx = 0, dy = 0;
    if (step == PlayerInput::MoveUp)
        dy = -1;
    else if (step == PlayerInput::MoveDown)
        dy = 1;
    else if (step == PlayerInput::MoveLeft)
        dx = -1;
    else if (step == PlayerInput::MoveRight)
        dx = 1;

    if (state.board[m_pos.y + dy][m_pos.x + dx] != TileType::Wall) {
        m_pos.x += dx;
        m_pos.y += dy;
    }
}
} // namespace DoomMan