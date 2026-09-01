#include "server/GameServerHost.h"

#include <QCoreApplication>
#include <QDebug>

#include "common/Types.h"
#include "server/GameEngineDriver.h"
#include "server/MapLoader.h"
#include "server/ServerNetworkManager.h"

namespace DoomMan {
void GameServerHost::start(int port) {
    srand(time(NULL));

    auto loadedState = MapLoader::loadMap("assets/levels/level1.txt");
    if (!loadedState) {
        throw std::runtime_error("Couldn't load the map");
    }

    m_gameState = *loadedState;
    m_engine = std::make_unique<GameEngineDriver>(m_gameState);
    m_networkManager = std::make_unique<ServerNetworkManager>(port);

    QObject::connect(m_networkManager.get(), &ServerNetworkManager::inputReceived, m_engine.get(),
                     &GameEngineDriver::processInput);

    QObject::connect(m_engine.get(), &GameEngineDriver::gameStateUpdated, this,
                     &GameServerHost::onEngineUpdate);
    m_engine->start();
}

void GameServerHost::handleJoinRequest(uint32_t playerId, const QString& nick) {
    for (auto& player : m_gameState.players) {
        if (player.id == playerId) {
            return;
        }
    }

    if (m_gameState.players.size() >= MAX_PLAYERS) {
        qDebug() << "Lobby is full, rejecting: " << nick;
        return;
    }

    bool slotFound = false;
    for (auto& player : m_gameState.players) {
        if (!player.name.isEmpty()) {
            continue;
        }

        player.id = playerId;
        player.name = nick;
        player.isAlive = true;
        player.isReady = false;
        slotFound = true;

        qDebug() << "Player " << nick << " joined at slot with ID:" << playerId;
        break;
    }

    if (!slotFound) {
        qDebug() << "No empty spawn points for player: " << nick;
        return;
    }

    m_gameState.players.push_back(DoomMan::PlayerState{});

    m_networkManager->broadcastState(m_gameState);
}

void GameServerHost::stop() {}

void GameServerHost::onEngineUpdate() {
    if (!m_networkManager) {
        return;
    }

    m_networkManager->broadcastState(m_gameState);
}
}  // namespace DoomMan