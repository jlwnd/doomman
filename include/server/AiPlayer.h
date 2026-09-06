#pragma once

#include <cstdint>

#include "common/Tiles.h"
#include "common/Types.h"

namespace DoomMan {
/// Sztuczny gracz (bot)
class AiPlayer {
   public:
    /// Domyślny odstęp między ruchami bota w ms (mniejszy = szybszy).
    static constexpr int DEFAULT_MOVE_INTERVAL_MS = 400;

    /// Tworzy bota sterującego graczem o zadanym id.
    /// @param playerId Id sterowanego gracza w GameState::players.
    /// @param speed Odstęp między ruchami w ms; domyślnie DEFAULT_MOVE_INTERVAL_MS.
    explicit AiPlayer(uint32_t playerId, int speed = DEFAULT_MOVE_INTERVAL_MS)
        : m_playerId(playerId), m_moveIntervalMs(speed) {}

    uint32_t m_playerId;  ///< Id sterowanego gracza w GameState::players.

    /// Wyznacza kolejny ruch bota.
    ///
    /// Kumuluje @p deltaMs; dopóki nie osiągnie odstępu ruchu, zwraca None.
    /// Po ruchu odnajduje gracza po @ref m_playerId, wybiera najbliższy
    /// wartościowy kafelek i deleguje pierwszy krok do Navigation::getNextMoveAStar.
    /// @param deltaMs Długość kroku symulacji (TICK_RATE_MS).
    /// @param state Aktualny stan gry.
    /// @return Kierunek ruchu; PlayerInput::None, gdy jeszcze nie czas na ruch,
    ///         gracza nie ma, nie żyje lub nie istnieje osiągalny cel.
    PlayerInput decideMove(int deltaMs, const GameState& state);

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

    int m_moveIntervalMs;       ///< Odstęp między ruchami w ms (mniejszy = szybszy).
    int m_timeAccumulator = 0;  ///< Nagromadzony czas od ostatniego ruchu (ms).
};
}  // namespace DoomMan
