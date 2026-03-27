#pragma once

#include <QElapsedTimer>
#include <QObject>
#include <QTimer>

#include "common/Types.h"
#include "server/Demon.h"
#include "server/demons/DemonSpawner.h"

namespace DoomMan {

class GameEngine : public QObject {
    Q_OBJECT
   public:
    explicit GameEngine(GameState& state, QObject* parent = nullptr);

    void start();

   public slots:
    void processInput(uint32_t playerId, PlayerInput input);

   signals:
    void gameStateUpdated();

   private slots:
    void tick();

   private:
    void movePlayer(PlayerState& player, int dx, int dy);
    void checkCollisions(PlayerState& player);

    void initDemons();
    void updateDemons();

    GameState& m_state;
    QTimer* m_timer;
    QElapsedTimer m_gameClock;

    std::vector<DemonSpawner> m_spawners;

    int m_berserkTimerMs = 0;
    int m_initialTime;
    const int TICK_RATE_MS = 100;
};

} // namespace DoomMan