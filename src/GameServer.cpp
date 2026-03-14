#include <QCoreApplication>
#include <QDebug>

#include "common/Types.h"
#include "server/GameEngine.h"
#include "server/MapLoader.h"
#include "server/NetworkManager.h"

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    auto loadedState = Doom::MapLoader::loadMap("assets/levels/level1.txt");
    if (!loadedState) return 1;

    Doom::GameState game = *loadedState;

    Doom::GameEngine engine(game);
    Doom::NetworkManager network(666);  // Listening on port 666 :)

    QObject::connect(&engine, &Doom::GameEngine::gameStateUpdated,
                     [&]() { network.broadcastState(game); });

    // 4. Start the simulation
    engine.start();

    qDebug() << "Server is running. Logic and Network are linked.";

    return a.exec();
}