#include "server/demons/Imp.h"

#include "server/Navigation.h"

namespace Doom {
void Imp::move(int deltaMs, const GameState& state, const PlayerState& target) {
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

    PlayerInput step = Navigation::getNextMoveAStar(m_pos, target.pos, state.board);

    int dx = 0;
    int dy = 0;
    switch (step) {
        case PlayerInput::MoveUp:
            dy = -1;
            break;
        case PlayerInput::MoveDown:
            dy = 1;
            break;
        case PlayerInput::MoveLeft:
            dx = -1;
            break;
        case PlayerInput::MoveRight:
            dx = 1;
            break;
        case PlayerInput::None:
            return;
    }

    const int newX = m_pos.x + dx;
    const int newY = m_pos.y + dy;

    // @TODO - abstract out these checks into another function to improve reuasbility
    if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE &&
        state.board[newY][newX] != TileType::Wall) {
        m_pos.x = newX;
        m_pos.y = newY;
    }
}
}  // namespace Doom