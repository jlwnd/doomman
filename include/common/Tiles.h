#pragma once

#include <compare>
#include <cstdint>

/// Rozmiar planszy w kafelkach - plansza jest kwadratem o wymiarach BOARD_SIZE × BOARD_SIZE.
inline constexpr int BOARD_SIZE = 21;

/// Rodzaj pojedynczego kafelka planszy.
enum class TileType : uint8_t {
    Empty,           ///< Pusty kafelek.
    Wall,            ///< Ściana labiryntu.
    Corridor,        ///< Korytarz z amunicją do zebrania.
    Berserk,         ///< Sfera Berserka.
    ImpSpawn,        ///< Punkt odrodzenia demona Imp.
    PinkySpawn,      ///< Punkt odrodzenia demona Pinky.
    CacodemonSpawn,  ///< Punkt odrodzenia demona Cacodemon.
    LostSoulSpawn    ///< Punkt odrodzenia demona Lost Soul.
};

/// Współrzędne (X, Y) na siatce planszy.
struct Position {
    int x = 0;  ///< Numer kolumny.
    int y = 0;  ///< Numer wiersza.

    /// Porównanie pozycji.
    auto operator<=>(const Position&) const = default;
};