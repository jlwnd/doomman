#include "server/GameEngine.h"

#include <QDebug>
#include <algorithm>

#include "server/demons/Cacodemon.h"
#include "server/demons/Imp.h"
#include "server/demons/Pinky.h"

namespace Doom {

GameEngine::GameEngine(GameState& state, QObject* parent)
    : QObject(parent), m_state(state), m_initialTime(state.timeLeftSeconds) {
    initDemons();

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
            player.lastInput = input == PlayerInput::None ? player.lastInput : input;
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

void GameEngine::initDemons() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (m_state.board[y][x] == TileType::SpawnPoint) {
                m_spawnPoints.push_back({x, y});
            }
        }
    }

    if (m_spawnPoints.empty()) {
        qWarning() << "[GameEngine]: No spawn points found on the map!";
        return;
    }

    // @TODO - change spawning mechanics
    m_demonAI.push_back(std::make_unique<Imp>(DemonType::Imp, m_spawnPoints[0]));
    m_demonAI.push_back(std::make_unique<Pinky>(DemonType::Pinky, m_spawnPoints[1]));
    m_demonAI.push_back(std::make_unique<Cacodemon>(DemonType::Cacodemon, m_spawnPoints[2]));

    for (size_t i = 0; i < m_demonAI.size() && i < DEMON_COUNT; i++) {
        m_state.demons[i].type = m_demonAI[i]->getType();
        m_state.demons[i].pos = m_demonAI[i]->getPosition();
        m_state.demons[i].isFrightened = m_demonAI[i]->isFrightened();
    }
}

void GameEngine::updateDemons() {
    PlayerState* target = nullptr;
    for (auto& p : m_state.players) {
        if (p.isAlive) {
            target = &p;
            break;
        }
    }

    if (!target) return;

    for (size_t i = 0; i < m_demonAI.size(); ++i) {
        m_demonAI[i]->move(TICK_RATE_MS, m_state, *target);

        m_state.demons[i].pos = m_demonAI[i]->getPosition();
        m_state.demons[i].isFrightened = m_demonAI[i]->isFrightened();

        if (m_state.demons[i].pos == target->pos) {
            if (m_state.demons[i].isFrightened) {
                target->score += 200;

                Position respawn = m_spawnPoints[rand() % m_spawnPoints.size()];

                m_demonAI[i] = std::make_unique<Imp>(DemonType::Imp, respawn);

            } else {
                target->isAlive = false;
                qDebug() << "[GameEngine]: Slayer has been eliminated by a demon!";
            }
        }
    }
}

}  // namespace Doom