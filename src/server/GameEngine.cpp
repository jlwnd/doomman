#include "server/GameEngine.h"

#include <QDebug>
#include <algorithm>

namespace Doom {

GameEngine::GameEngine(GameState& state, QObject* parent)
    : QObject(parent), m_state(state), m_initialTime(state.timeLeftSeconds) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameEngine::tick);
}

void GameEngine::start() {
    m_gameClock.start();
    m_timer->start(TICK_RATE_MS);
}

void GameEngine::tick() {
    qint64 msPassed = m_gameClock.elapsed();
    int secondsPassed = static_cast<int>(msPassed / 1000);
    m_state.timeLeftSeconds = std::max(0, m_initialTime - secondsPassed);

    updateDemons();

    emit gameStateUpdated();
}

void GameEngine::processInput(uint32_t playerId, PlayerInput input) {
    int dx = 0;
    int dy = 0;

    switch (input) {
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
        default:
            return;
    }

    for (auto& player : m_state.players) {
        if (player.id == playerId && player.isAlive) {
            movePlayer(player, dx, dy);
            break;
        }
    }
}

void GameEngine::movePlayer(PlayerState& player, int dx, int dy) {
    int newX = player.pos.x + dx;
    int newY = player.pos.y + dy;

    if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
        if (m_state.board[newY][newX] != TileType::Wall) {
            player.pos.x = newX;
            player.pos.y = newY;
            checkCollisions(player);
        }
    }
}

void GameEngine::checkCollisions(PlayerState& player) {
    auto& tile = m_state.board[player.pos.y][player.pos.x];

    if (tile == TileType::Berserk) {
        player.hasBerserk = true;
        tile = TileType::Empty;
    } else if (tile == TileType::Corridor) {
        player.score += 10;
        tile = TileType::Empty;
    }
}

void GameEngine::updateDemons() {
    // AI logic will be implemented here
}

}  // namespace Doom