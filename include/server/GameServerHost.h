#pragma once
#include <QCoreApplication>

#include "common/Types.h"
#include "server/GameEngine.h"
#include "server/ServerNetworkManager.h"

namespace DoomMan {

/// Host serwera – spina silnik gry z warstwą sieciową w jedną całość.
class GameServerHost : public QObject {
   public:
    /// Uruchamia serwer nasłuchujący na zadanym porcie.
    /// @param port Port TCP nasłuchu.
    void start(int port);

    /// Zatrzymuje serwer i kończy rozgrywkę.
    void stop();

    /// Obsługuje prośbę gracza o dołączenie do gry.
    /// @param playerId Identyfikator gracza.
    /// @param nick Pseudonim gracza.
    void handleJoinRequest(uint32_t playerId, const QString& nick);

   private slots:
    void onEngineUpdate();

   private:
    GameState m_gameState;
    std::unique_ptr<GameEngine> m_engine;
    std::unique_ptr<ServerNetworkManager> m_networkManager;
};

}  // namespace DoomMan