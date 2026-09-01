#pragma once

/// @file
/// @brief Reprezentacja planszy gry.

#include <common/Grid.h>
#include <common/Tiles.h>

#include <array>

namespace DoomMan {
/// Plansza gry – labirynt kafelków o rozmiarze BOARD_SIZE × BOARD_SIZE.
class Map {
   public:
    /// Sprawdza, czy pozycja mieści się w granicach planszy.
    /// @param p Sprawdzana pozycja.
    /// @return true, jeśli pozycja leży wewnątrz planszy.
    bool isBounds(Position p) const;

    /// Sprawdza, czy na pozycji znajduje się ściana.
    /// @param p Sprawdzana pozycja.
    /// @return true, jeśli kafelek jest ścianą (lub poza planszą).
    bool isWall(Position p) const;

    /// Zwraca rodzaj kafelka na zadanej pozycji.
    /// @param p Pozycja kafelka.
    /// @return Typ kafelka na tej pozycji.
    TileType at(Position p) const;

    /// Ustawia rodzaj kafelka na zadanej pozycji.
    /// @param p Pozycja kafelka.
    /// @param t Nowy typ kafelka.
    void set(Position p, TileType t);

    /// Zwraca wszystkie kafelki planszy do odczytu.
    /// @return Stała referencja do tablicy kafelków.
    const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& tiles() const;
}  // namespace DoomMan