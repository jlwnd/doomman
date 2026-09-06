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

    auto loadedLevel = MapLoader::loadMap("assets/levels/level1.txt");
    if (!loadedLevel) {
        throw std::runtime_error("Couldn't load the map");
    }

    m_gameState = loadedLevel->state;
    m_spawns = loadedLevel->spawns;
    m_engine = std::make_unique<GameEngineDriver>(m_gameState);
    m_networkManager = std::make_unique<ServerNetworkManager>(port);

    QObject::connect(m_networkManager.get(), &ServerNetworkManager::inputReceived, m_engine.get(),
                     &GameEngineDriver::processInput);

    QObject::connect(m_networkManager.get(), &ServerNetworkManager::joinRequested, this,
                     &GameServerHost::handleJoinRequest);

    QObject::connect(m_engine.get(), &GameEngineDriver::gameStateUpdated, this,
                     &GameServerHost::onEngineUpdate);

    spawnAiPlayer("BOT");  // @Todo: remove the bot

    m_engine->start();
}

void GameServerHost::spawnAiPlayer(const QString& nick) {
    uint32_t botId = m_networkManager->allocatePlayerId();
    handleJoinRequest(botId, nick);
    m_aiPlayers.push_back(AiPlayer{botId});
}

void GameServerHost::handleJoinRequest(uint32_t playerId, const QString& nick) {
    for (auto& player : m_gameState.players) {
        if (player.id == playerId) {
            return;
        }
    }

    if (m_nextSpawn >= m_spawns.size()) {
        qDebug() << "[GameServer] No free spawn points, rejecting: " << nick;
        return;
    }

    m_gameState.players.push_back(
        PlayerState{.id = playerId, .pos = m_spawns[m_nextSpawn++], .name = nick});

    qDebug() << "[GameServer] Player " << nick << " joined with ID:" << playerId;

    m_networkManager->broadcastState(m_gameState);
}

void GameServerHost::stop() {}

void GameServerHost::onEngineUpdate() {
    if (!m_networkManager) {
        return;
    }

    for (const AiPlayer& bot : m_aiPlayers) {
        m_engine->processInput(bot.m_playerId, bot.decideMove(m_gameState));
    }

    m_networkManager->broadcastState(m_gameState);
}
}  // namespace DoomMan