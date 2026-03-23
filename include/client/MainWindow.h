#pragma once
#include <QMainWindow>
#include <QStackedWidget>

#include "client/GameWidget.h"
#include "client/MainMenuWidget.h"
#include "client/NetworkManager.h"

namespace Doom {
class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget* parent = nullptr);

   private slots:
    void handleHostGame(const QString& nick);
    void handleJoinGame(const QString& nick);
    void handleExit();

   private:
    QStackedWidget* m_stackedWidget;
    MainMenuWidget* m_mainMenu;
    GameWidget* m_gameView;
    ClientNetworkManager* m_networkManager;
};
}  // namespace Doom
