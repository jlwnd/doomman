#include <QCoreApplication>
#include <QDebug>

#include "common/Types.h"
#include "server/GameEngine.h"
#include "server/MapLoader.h"
#include "server/ServerNetworkManager.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    QCoreApplication a(argc, argv);

    auto loadedState = DoomMan::MapLoader::loadMap("assets/levels/level1.txt");
    if (!loadedState) return 1;

    DoomMan::GameState game = *loadedState;

    if (!game.players.empty()) {
        game.players[0].id = 0;
    }

    DoomMan::GameEngine engine(game);
    DoomMan::ServerNetworkManager network(666);  // Listening on port 666 >:)

    QObject::connect(&engine, &DoomMan::GameEngine::gameStateUpdated,
                     [&]() { network.broadcastState(game); });

    QObject::connect(&network, &DoomMan::ServerNetworkManager::inputReceived, &engine,
                     &DoomMan::GameEngine::processInput);

    engine.start();

    qDebug() << "Server is running. Logic and Network are linked.";

    return a.exec();
}