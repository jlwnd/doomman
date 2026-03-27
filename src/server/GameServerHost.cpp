#include "server/GameServerHost.h"

#include <QCoreApplication>

#include "common/Types.h"
#include "server/GameEngine.h"
#include "server/MapLoader.h"
#include "server/ServerNetworkManager.h"

namespace Doom {
void GameServerHost::start(int port) {
    srand(time(NULL));

    auto loadedState = MapLoader::loadMap("assets/levels/level1.txt");
    if (!loadedState) {
        throw std::runtime_error("Couldn't load the map");
    }

    m_gameState = *loadedState;
    m_engine = std::make_unique<GameEngine>(m_gameState);
    m_networkManager = std::make_unique<ServerNetworkManager>(port);

    QObject::connect(m_networkManager.get(), &ServerNetworkManager::inputReceived, m_engine.get(),
                     &GameEngine::processInput);

    QObject::connect(m_engine.get(), &GameEngine::gameStateUpdated, this,
                     &GameServerHost::onEngineUpdate);
    m_engine->start();
}

void GameServerHost::stop() {}

void GameServerHost::onEngineUpdate() {
    if (!m_networkManager) {
        return;
    }

    m_networkManager->broadcastState(m_gameState);
}
}  // namespace Doom