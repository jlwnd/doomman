#include "server/GameEngine.h"

#include <QDebug>
#include <algorithm>

#include "server/demons/DemonSpawner.h"

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

    if (m_berserkTimerMs > 0) {
        m_berserkTimerMs -= TICK_RATE_MS;
        if (m_berserkTimerMs <= 0) {
            m_berserkTimerMs = 0;
            for (auto& p : m_state.players) p.hasBerserk = false;
            for (auto& spawner : m_spawners) {
                if (auto* demon = spawner.getDemon()) demon->setFrightened(false);
            }
        }
    }

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
        m_berserkTimerMs = 10000;
        for (auto& spawner : m_spawners) {
            if (auto* demon = spawner.getDemon()) {
                demon->setFrightened(true);
            }
        }
        tile = TileType::Empty;
    } else if (tile == TileType::Corridor) {
        player.score += 10;
        tile = TileType::Empty;
    }
}

void GameEngine::initDemons() {
    m_spawners.clear();

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            switch (m_state.board[y][x]) {
                case TileType::ImpSpawn:
                    m_spawners.emplace_back(DemonType::Imp, Position{x, y});
                    break;
                case TileType::PinkySpawn:
                    m_spawners.emplace_back(DemonType::Pinky, Position{x, y});
                    break;
                case TileType::CacodemonSpawn:
                    m_spawners.emplace_back(DemonType::Cacodemon, Position{x, y});
                    break;
                case TileType::LostSoulSpawn:
                    m_spawners.emplace_back(DemonType::LostSoul, Position{x, y});
                    break;
                default:
                    continue;
            }
        }
    }

    if (m_spawners.empty()) {
        qWarning() << "[GameEngine]: No spawn points found on the map!";
        return;
    }

    for (size_t i = 0; i < m_spawners.size(); i++) {
        auto* demon = m_spawners[i].getDemon();
        m_state.demons[i].type = demon->getType();
        m_state.demons[i].pos = demon->getPosition();
        m_state.demons[i].isFrightened = demon->isFrightened();
        m_state.demons[i].isAlive = true;
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

    for (size_t i = 0; i < m_spawners.size(); ++i) {
        auto& spawner = m_spawners[i];
        auto* demon = spawner.getDemon();

        if (demon) {
            demon->move(TICK_RATE_MS, m_state, *target);

            m_state.demons[i].pos = demon->getPosition();
            m_state.demons[i].isFrightened = demon->isFrightened();
            m_state.demons[i].type = demon->getType();
            m_state.demons[i].isAlive = true;

            if (m_state.demons[i].pos == target->pos) {
                if (m_state.demons[i].isFrightened) {
                    target->score += 200;
                    spawner.notifyDemonDeath();
                    m_state.demons[i].isAlive = false;
                } else {
                    target->isAlive = false;
                    qDebug() << "[GameEngine]: Slayer has been eliminated by a demon!";
                }
            }
        } else {
            spawner.update(TICK_RATE_MS);
            demon = spawner.getDemon();
            if (demon) {
                m_state.demons[i].pos = demon->getPosition();
                m_state.demons[i].type = demon->getType();
                m_state.demons[i].isFrightened = demon->isFrightened();
                m_state.demons[i].isAlive = true;
            } else {
                m_state.demons[i].isAlive = false;
            }
        }
    }
}

}  // namespace Doom