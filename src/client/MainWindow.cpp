#include "client/MainWindow.h"

#include <QApplication>
#include <QDebug>

namespace Doom {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_mainMenu = new MainMenuWidget(this);
    m_gameView = new GameWidget(this);
    m_networkManager = new ClientNetworkManager(this);

    m_stackedWidget->addWidget(m_mainMenu);
    m_stackedWidget->addWidget(m_gameView);

    connect(m_mainMenu, &MainMenuWidget::sigHostGame, this, &MainWindow::handleHostGame);
    connect(m_mainMenu, &MainMenuWidget::sigJoinGame, this, &MainWindow::handleJoinGame);
    connect(m_mainMenu, &MainMenuWidget::sigExit, this, &MainWindow::handleExit);

    connect(m_networkManager, &ClientNetworkManager::gameStateReceived, m_gameView,
            &GameWidget::updateState);
    connect(m_gameView, &GameWidget::inputDetected, m_networkManager,
            &ClientNetworkManager::sendInput);

    setWindowTitle("DoomMan");
    resize(640, 640);
    
    setStyleSheet("QMainWindow { background-color: #0b0c10; }");
    
    m_stackedWidget->setCurrentWidget(m_mainMenu);
}

void MainWindow::handleHostGame(const QString& nick) {
    qDebug() << "Host game clicked with nick:" << nick;
    // @TODO: Implement lobby/server creation
    m_stackedWidget->setCurrentWidget(m_gameView);
    m_networkManager->connectToServer("127.0.0.1", 666);
}

void MainWindow::handleJoinGame(const QString& nick) {
    qDebug() << "Join game clicked with nick:" << nick;
    // @TODO: Implement lobby/server joining
    m_stackedWidget->setCurrentWidget(m_gameView);
    m_networkManager->connectToServer("127.0.0.1", 666);
}

void MainWindow::handleExit() {
    QApplication::quit();
}

}  // namespace Doom
