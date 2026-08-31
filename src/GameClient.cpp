#include <QApplication>

#include "client/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    DoomMan::GameWidget gameView;
    DoomMan::ClientNetworkManager network;

    QObject::connect(&network, &DoomMan::ClientNetworkManager::gameStateReceived, &gameView,
                     &DoomMan::GameWidget::updateState);

    QObject::connect(&gameView, &DoomMan::GameWidget::inputDetected, &network,
                     &DoomMan::ClientNetworkManager::sendInput);

    gameView.setWindowTitle("DoomMan Client");
    gameView.resize(640, 640);
    gameView.show();

    qDebug() << "Connecting to server...";
    network.connectToServer("127.0.0.1", 666);

    return a.exec();
}