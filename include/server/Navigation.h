#pragma once
#include <deque>
#include <vector>

#include "common/Types.h"

namespace DoomMan {
/// Węzeł używany przez algorytm A* do wyznaczania trasy.
struct Node {
    Position pos;     ///< Pozycja węzła na planszy.
    int g;            ///< Koszt dotarcia od startu do tego węzła.
    int h;            ///< Heurystyczny szacunek kosztu do celu.
    Position parent;  ///< Pozycja poprzednika.

    /// @return Całkowity koszt węzła (g + h).
    int f() const {
        return g + h;
    }

    /// Porównanie po koszcie f.
    /// @param other Węzeł porównywany.
    /// @return true, jeśli ten węzeł ma większy koszt f niż other.
    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

/// Statyczne narzędzia nawigacji po planszy.
class Navigation {
   public:
    /// Wyznacza pierwszy krok najkrótszej ścieżki algorytmem A*.
    /// @param start Pozycja startowa.
    /// @param target Pozycja docelowa.
    /// @param board Plansza z kafelkami.
    /// @return Kierunek pierwszego kroku w stronę celu.
    static PlayerInput getNextMoveAStar(
        const Position& start, const Position& target,
        const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& board);

    /// Oblicza odległość Manhattan między dwoma pozycjami.
    /// @param a Pierwsza pozycja.
    /// @param b Druga pozycja.
    /// @return Odległość Manhattan między a i b.
    static int distanceBetween(const Position& a, const Position& b);
};
}  // namespace DoomMan