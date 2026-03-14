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

    if (!game.players.empty()) {
        game.players[0].id = 0;
    }

    Doom::GameEngine engine(game);
    Doom::NetworkManager network(666);  // Listening on port 666 >:)

    QObject::connect(&engine, &Doom::GameEngine::gameStateUpdated,
                     [&]() { network.broadcastState(game); });

    QObject::connect(&network, &Doom::NetworkManager::inputReceived, &engine,
                     &Doom::GameEngine::processInput);

    // 4. Start the simulation
    engine.start();

    qDebug() << "Server is running. Logic and Network are linked.";

    return a.exec();
}