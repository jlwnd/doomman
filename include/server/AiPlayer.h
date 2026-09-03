#pragma once

#include <cstdint>

#include "common/Tiles.h"
#include "common/Types.h"

namespace DoomMan {
/// Sztuczny gracz (bot)
class AiPlayer {
   public:
    uint32_t m_playerId;  ///< Id sterowanego gracza w GameState::players.

    /// Wyznacza kolejny ruch bota na podstawie aktualnego stanu gry.
    ///
    /// Odnajduje sterowanego gracza po @ref m_playerId, wybiera najbliższy
    /// wartościowy kafelek i deleguje pierwszy krok do Navigation::getNextMoveAStar.
    /// @param state Aktualny stan gry.
    /// @return Kierunek ruchu; PlayerInput::None, gdy gracza nie ma, nie żyje
    ///         lub nie istnieje osiągalny cel.
    PlayerInput decideMove(const GameState& state) const;

   private:
    /// Znajduje najbliższy wartościowy kafelek (Corridor lub Berserk) osiągalny
    /// bez przechodzenia przez ściany.
    ///
    /// Wykorzystuje przeszukiwanie wszerz (BFS), więc odległość liczona jest
    /// po realnej ścieżce, a nie w odległości Manhattan. Kafelek startowy jest
    /// pomijany, aby bot nie stawał w miejscu na już zajmowanym polu.
    /// @param state Aktualny stan gry.
    /// @param currentPos Pozycja startowa (pozycja bota).
    /// @return Pozycja najbliższego celu; równa @p currentPos, gdy nic nie jest osiągalne.
    Position findClosestValuableTarget(const GameState& state, const Position currentPos) const;

    /// Wyszukuje żyjącego gracza o zadanym id na liście graczy.
    /// @param state Aktualny stan gry.
    /// @param playerId Szukane id gracza.
    /// @return Kopia stanu gracza; domyślny PlayerState (id 0), gdy nie znaleziono.
    PlayerState findPlayerWithId(const GameState& state, const uint32_t playerId) const;
};
}  // namespace DoomMan
