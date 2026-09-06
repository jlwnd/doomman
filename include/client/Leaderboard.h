#pragma once

#include <cstdint>
#include <vector>

#include <QString>

#include "common/Types.h"

namespace DoomMan {
/// Pojedynczy wiersz tablicy wyników.
struct ScoreEntry {
    int place = 0;         ///< Miejsce w rankingu (1 = najlepszy).
    QString name;          ///< Pseudonim gracza.
    uint32_t score = 0;    ///< Zdobyte punkty.
};

/// Ranking graczy – uszeregowuje wyniki malejąco i przypisuje miejsca.
/// Kliencki obiekt logiki: zdejmuje sortowanie z widżetów.
class Leaderboard {
   public:
    /// Buduje ranking na podstawie listy graczy.
    /// @param players Gracze do uszeregowania.
    explicit Leaderboard(const std::vector<PlayerState>& players);

    /// @return Wiersze rankingu w kolejności od najlepszego wyniku.
    const std::vector<ScoreEntry>& entries() const;

   private:
    std::vector<ScoreEntry> m_entries;
};
}  // namespace DoomMan
