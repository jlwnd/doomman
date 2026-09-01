#pragma once

#include <array>

namespace DoomMan {
/// Kwadratowa siatka N × N przechowująca elementy typu T.
/// @tparam T Typ przechowywanego elementu.
/// @tparam N Długość boku siatki (liczba kafelków w wierszu i kolumnie).
template <typename T, int N>
class Grid {
   public:
    /// Zwraca kopię elementu na zadanych współrzędnych.
    /// @param x Kolumna.
    /// @param y Wiersz.
    /// @return Element znajdujący się w komórce (x, y).
    T at(int x, int y) const;

    /// Zwraca referencję do elementu na zadanych współrzędnych.
    /// @param x Kolumna.
    /// @param y Wiersz.
    /// @return Referencja do komórki (x, y).
    T& at(int x, int y);

    /// Wypełnia całą siatkę podaną wartością.
    /// @param value Wartość wpisywana do każdej komórki.
    void fill(const T& value);

    /// Sprawdza, czy współrzędne mieszczą się w granicach siatki.
    /// @param x Kolumna.
    /// @param y Wiersz.
    /// @return true, jeśli (x, y) leży wewnątrz siatki.
    bool inBounds(int x, int y) const;

    /// Zwraca wszystkie wiersze siatki do odczytu.
    /// @return Stała referencja do wewnętrznej tablicy wierszy.
    const std::array<std::array<T, N>, N>& rows() const;
};
}  // namespace DoomMan