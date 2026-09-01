#pragma once

#include <array>

namespace DoomMan {
template <typename T, int N>
class Grid {
   private:
    std::array<std::array<T, N>, N> m_data{};

   public:
    T at(int x, int y) const {
        return m_data[y][x];
    }
    T& at(int x, int y) {
        return m_data[y][x];
    }
    void fill(const T& value) {
        for (int y = 0; y < N; ++y)
            for (int x = 0; x < N; ++x) m_data[y][x] = value;
    }
    bool inBounds(int x, int y) const {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
    const std::array<std::array<T, N>, N>& rows() const {
        return m_data;
    }
};
}  // namespace DoomMan