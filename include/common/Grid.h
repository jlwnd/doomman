#pragma once

#include <array>

namespace DoomMan {
/// Kwadratowa siatka N × N przechowująca elementy typu T.
/// @tparam T Typ przechowywanego elementu.
/// @tparam N Długość boku siatki (liczba kafelków w wierszu i kolumnie).
template <typename T, int N>
class Grid {
   private:
    std::array<std::array<T, N>, N> m_data{};

   public:
    /// Zwraca kopię elementu na zadanych współrzędnych.
    /// @param x Kolumna.
    /// @param y Wiersz.
    /// @return Element znajdujący się w komórce (x, y).
    T at(int x, int y) const {
        return m_data[y][x];
    }

    /// Zwraca referencję do elementu na zadanych współrzędnych.
    /// @param x Kolumna.
    /// @param y Wiersz.
    /// @return Referencja do komórki (x, y).
    T& at(int x, int y) {
        return m_data[y][x];
    }

    /// Wypełnia całą siatkę podaną wartością.
    /// @param value Wartość wpisywana do każdej komórki.
    void fill(const T& value) {
        for (int y = 0; y < N; ++y)
            for (int x = 0; x < N; ++x) m_data[y][x] = value;
    }

    /// Sprawdza, czy współrzędne mieszczą się w granicach siatki.
    /// @param x Kolumna.
    /// @param y Wiersz.
    /// @return true, jeśli (x, y) leży wewnątrz siatki.
    bool inBounds(int x, int y) const {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    /// Zwraca wszystkie wiersze siatki do odczytu.
    /// @return Stała referencja do wewnętrznej tablicy wierszy.
    const std::array<std::array<T, N>, N>& rows() const {
        return m_data;
    }
};
}  // namespace DoomMan