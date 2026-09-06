#include "client/MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

#include "client/widgets/LobbyWidget.h"

namespace DoomMan {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_mainMenu = new MainMenuWidget(this);
    m_gameView = new GameWidget(this);
    m_lobbyView = new LobbyWidget(this);
    m_networkManager = new ClientNetworkManager(this);

    m_gamePage = new QWidget(this);
    m_scoreLabel = new QLabel("Score: 0", m_gamePage);
    m_scoreLabel->setStyleSheet("color: white; font-size: 20px; font-weight: bold; padding: 6px;");
    auto* gameLayout = new QVBoxLayout(m_gamePage);
    gameLayout->setContentsMargins(0, 0, 0, 0);
    gameLayout->setSpacing(0);
    gameLayout->addWidget(m_scoreLabel, 0, Qt::AlignHCenter);
    gameLayout->addWidget(m_gameView, 0, Qt::AlignHCenter);

    m_stackedWidget->addWidget(m_mainMenu);
    m_stackedWidget->addWidget(m_gamePage);
    m_stackedWidget->addWidget(m_lobbyView);

    connect(m_mainMenu, &MainMenuWidget::sigHostGame, this, &MainWindow::handleHostGame);
    connect(m_mainMenu, &MainMenuWidget::sigJoinGame, this, &MainWindow::handleJoinGame);
    connect(m_mainMenu, &MainMenuWidget::sigExit, this, &MainWindow::handleExit);

    connect(m_networkManager, &ClientNetworkManager::gameStateReceived, m_gameView,
            &GameWidget::updateState);
    connect(m_gameView, &GameWidget::inputDetected, m_networkManager,
            &ClientNetworkManager::sendInput);

    connect(m_networkManager, &ClientNetworkManager::gameStateReceived, m_lobbyView,
            &LobbyWidget::updateLobby);
    connect(m_lobbyView, &LobbyWidget::sigGameReady, m_networkManager,
            &ClientNetworkManager::sendReady);
    connect(m_lobbyView, &LobbyWidget::sigGameStart, m_networkManager,
            &ClientNetworkManager::sendStart);

    connect(m_networkManager, &ClientNetworkManager::gameStateReceived, this,
            [this](const GameState& state) {
                for (const auto& p : state.players) {
                    if (p.name == m_nick) {
                        m_scoreLabel->setText(QString("Score: %1").arg(p.score));
                        break;
                    }
                }
                if (state.mode == GameMode::InGame) {
                    m_stackedWidget->setCurrentWidget(m_gamePage);
                }
            });

    setWindowTitle("DoomMan");
    resize(672, 720);

    setStyleSheet("QMainWindow { background-color: #0b0c10; }");

    m_stackedWidget->setCurrentWidget(m_mainMenu);
}

void MainWindow::handleHostGame(const QString& nick) {
    qDebug() << "Host game clicked with nick:" << nick;
    m_nick = nick;

    m_localServer = std::make_unique<GameServerHost>();

    try {
        m_localServer->start(666);
    } catch (const std::exception& e) {
        qCritical() << "Server couldn't start: " << e.what();
        return;
    }

    m_lobbyView->setHost(true);
    m_stackedWidget->setCurrentWidget(m_lobbyView);
    m_networkManager->connectToServer("127.0.0.1", 666, nick);
}

void MainWindow::handleJoinGame(const QString& nick) {
    qDebug() << "Join game clicked with nick:" << nick;
    m_nick = nick;
    m_lobbyView->setHost(false);
    m_stackedWidget->setCurrentWidget(m_lobbyView);
    m_networkManager->connectToServer("127.0.0.1", 666, nick);
}

void MainWindow::handleExit() {
    QApplication::quit();
}

}  // namespace DoomMan
