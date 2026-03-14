#include <QApplication>
#include <QDebug>

#include "client/GameWidget.h"
#include "client/NetworkManager.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    Doom::GameWidget gameView;
    Doom::ClientNetworkManager network;

    QObject::connect(&network, &Doom::ClientNetworkManager::gameStateReceived, &gameView,
                     &Doom::GameWidget::updateState);

    QObject::connect(&gameView, &Doom::GameWidget::inputDetected, &network,
                     &Doom::ClientNetworkManager::sendInput);

    gameView.setWindowTitle("DoomMan Client");
    gameView.resize(640, 640);
    gameView.show();

    qDebug() << "Connecting to server...";
    network.connectToServer("127.0.0.1", 666);

    return a.exec();
}