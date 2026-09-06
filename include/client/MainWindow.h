#pragma once
#include <QLabel>
#include <QMainWindow>
#include <QStackedWidget>

#include "client/NetworkManager.h"
#include "client/widgets/GameOverWidget.h"
#include "client/widgets/GameWidget.h"
#include "client/widgets/LobbyWidget.h"
#include "client/widgets/MainMenuWidget.h"
#include "server/GameServerHost.h"

namespace DoomMan {
/// Główne okno aplikacji – zarządza przełączaniem ekranów
/// (menu, gra, lobby) za pomocą QStackedWidget.
class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    /// Tworzy główne okno aplikacji.
    /// @param parent Widżet-rodzic Qt.
    explicit MainWindow(QWidget* parent = nullptr);

   private slots:
    void handleHostGame(const QString& nick);
    void handleJoinGame(const QString& nick);
    void handleGameState(const GameState& state);
    void handleExit();

   private:
    QStackedWidget* m_stackedWidget;
    MainMenuWidget* m_mainMenu;
    GameWidget* m_gameView;
    QWidget* m_gamePage;
    QLabel* m_scoreLabel;
    LobbyWidget* m_lobbyView;
    GameOverWidget* m_gameOverView;
    QString m_nick;
    bool m_gameOverShown = false;

    ClientNetworkManager* m_networkManager;
    std::unique_ptr<GameServerHost> m_localServer;
};
}  // namespace DoomMan
