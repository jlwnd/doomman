#pragma once

#include <QObject>
#include <QTimer>
#include <cstdint>

#include "common/Types.h"
#include "server/GameEngine.h"

namespace DoomMan {
/// Adapter Qt dla silnika gry: zarządza cyklem czasowym (QTimer),
/// w każdym kroku aktualizuje symulację i sygnalizuje zmianę stanu.
class GameEngineDriver : public QObject {
    Q_OBJECT
   public:
    /// Tworzy adapter operujący na współdzielonym stanie gry.
    /// @param state Referencja do stanu gry aktualizowanego przez silnik.
    /// @param parent Obiekt-rodzic Qt.
    explicit GameEngineDriver(GameState& state, QObject* parent = nullptr);
    /// Uruchamia pętlę czasową rozgrywki.
    void start();

   public slots:
    /// Przekazuje kierunek ruchu odebrany od gracza do silnika.
    /// @param playerId Identyfikator gracza.
    /// @param input Wciśnięty kierunek ruchu.
    void processInput(uint32_t playerId, PlayerInput input);

   signals:
    /// Emitowany po każdej aktualizacji stanu gry (do rozesłania klientom).
    void gameStateUpdated();

   private slots:
    void tick();

   private:
    GameEngine m_engine;
    QTimer* m_timer;
    const int TICK_RATE_MS = 100;
};
}  // namespace DoomMan