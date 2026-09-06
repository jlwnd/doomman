#pragma once

#include "common/Types.h"
#include "server/demons/DemonSpawner.h"

namespace DoomMan {

/// Serce serwera – w pętli czasowej (tick) przetwarza logikę gry,
/// wykrywa kolizje i zarządza czasem trwania bonusów.
class GameEngine {
   public:
    /// Tworzy silnik operujący na współdzielonym stanie gry.
    /// @param state Referencja do stanu gry aktualizowanego przez silnik.
    explicit GameEngine(GameState& state);

    /// Posuwa symulację o zadany krok czasu: przetwarza logikę gry,
    /// aktualizuje demony, odlicza czas i wykrywa kolizje.
    /// Wołana z pętli czasowej (timer), z testu lub z pętli headless.
    /// @param deltaMs Czas, jaki upłynął od poprzedniego kroku, w milisekundach.
    void step(int deltaMs);

   public:
    /// Przetwarza kierunek ruchu odebrany od gracza.
    /// @param playerId Identyfikator gracza.
    /// @param input Wciśnięty kierunek ruchu.
    void processInput(uint32_t playerId, PlayerInput input);

   private:
    void movePlayer(PlayerState& player, int dx, int dy);
    void checkCollisions(PlayerState& player);

    void initDemons();
    void updateDemons();

    GameState& m_state;

    std::vector<DemonSpawner> m_spawners;

    int m_berserkTimerMs = 0;
    int m_msAccumulator = 0;
};

}  // namespace DoomMan
