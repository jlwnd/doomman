#pragma once

#include <QElapsedTimer>
#include <QObject>
#include <QTimer>

#include "common/Types.h"

namespace Doom {

class GameEngine : public QObject {
    Q_OBJECT
   public:
    explicit GameEngine(GameState& state, QObject* parent = nullptr);

    void start();
    void processInput(uint32_t playerId, int dx, int dy);

   signals:
    void gameStateUpdated();

   private slots:
    void tick();

   private:
    void movePlayer(PlayerState& player, int dx, int dy);
    void checkCollisions(PlayerState& player);
    void updateDemons();

    GameState& m_state;
    QTimer* m_timer;
    QElapsedTimer m_gameClock;

    int m_initialTime;
    const int TICK_RATE_MS = 100;
};

}  // namespace Doom