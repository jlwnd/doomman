#include "server/GameEngine.h"

#include <QDebug>
#include <algorithm>

namespace DoomMan {

GameEngine::GameEngine(GameState& state) : m_state(state) {
    initDemons();
}

void GameEngine::step(int deltaMs) {
    m_msAccumulator += deltaMs;
    while (m_msAccumulator >= 1000) {
        m_msAccumulator -= 1000;
        m_state.timeLeftSeconds = std::max(0, m_state.timeLeftSeconds - 1);
    }

    if (m_berserkTimerMs > 0) {
        m_berserkTimerMs -= deltaMs;
        if (m_berserkTimerMs <= 0) {
            m_berserkTimerMs = 0;
            m_berserkChainCount = 0;
            for (auto& p : m_state.players) p.hasBerserk = false;
            for (auto& spawner : m_spawners) {
                if (auto* demon = spawner.getDemon()) demon->setFrightened(false);
            }
        }
    }

    updateDemons();
    checkDemonCollisions();
}

void GameEngine::checkDemonCollisions() {
    for (size_t i = 0; i < m_spawners.size(); i++) {
        auto* demon = m_spawners[i].getDemon();
        if (!demon) continue;

        for (auto& player : m_state.players) {
            if (!player.isAlive || player.pos != demon->getPosition()) continue;

            if (demon->isFrightened()) {
                uint32_t reward = SCORE_PER_DEMON;
                for (int j = 0; j < m_berserkChainCount; j++) {
                    reward *= 2;
                }
                player.score += reward;
                if (m_berserkChainCount < 3) m_berserkChainCount++;
                m_spawners[i].notifyDemonDeath();
                m_state.demons[i].isAlive = false;
                break;
            }

            player.isAlive = false;
        }
    }
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
        if (!m_state.board.isWall({newX, newY})) {
            player.pos.x = newX;
            player.pos.y = newY;
            checkCollisions(player);
            checkDemonCollisions();
        }
    }
}

void GameEngine::checkCollisions(PlayerState& player) {
    auto tile = m_state.board.at(player.pos);

    if (tile == TileType::Berserk) {
        player.hasBerserk = true;
        m_berserkTimerMs = 10000;
        m_berserkChainCount = 0;
        for (auto& spawner : m_spawners) {
            if (auto* demon = spawner.getDemon()) {
                demon->setFrightened(true);
            }
        }
        m_state.board.set(player.pos, TileType::Empty);
    } else if (tile == TileType::Corridor) {
        player.score += SCORE_PER_PELLET;
        m_state.board.set(player.pos, TileType::Empty);
    }
}

void GameEngine::updateDemons() {
    const PlayerState* target = nullptr;
    for (const auto& p : m_state.players) {
        if (p.isAlive) {
            target = &p;
            break;
        }
    }

    for (size_t i = 0; i < m_spawners.size(); i++) {
        auto& spawner = m_spawners[i];
        spawner.update(TICK_RATE_MS);

        auto* demon = spawner.getDemon();
        if (demon && target) {
            demon->move(TICK_RATE_MS, m_state, *target);
        }

        if (demon) {
            m_state.demons[i].type = demon->getType();
            m_state.demons[i].pos = demon->getPosition();
            m_state.demons[i].isFrightened = demon->isFrightened();
            m_state.demons[i].isAlive = true;
        } else {
            m_state.demons[i].isAlive = false;
        }
    }
}

void GameEngine::initDemons() {
    m_spawners.clear();

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            switch (m_state.board.at({x, y})) {
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

}  // namespace DoomMan
