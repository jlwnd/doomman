#pragma once
#include <QCoreApplication>

#include "common/Types.h"
#include "server/GameEngine.h"
#include "server/ServerNetworkManager.h"

namespace DoomMan {

class GameServerHost : public QObject {
   public:
    void start(int port);
    void stop();
    void handleJoinRequest(uint32_t playerId, const QString& nick);

   private slots:
    void onEngineUpdate();

   private:
    GameState m_gameState;
    std::unique_ptr<GameEngine> m_engine;
    std::unique_ptr<ServerNetworkManager> m_networkManager;
};

}  // namespace DoomMan