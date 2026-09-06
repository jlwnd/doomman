#include "client/Leaderboard.h"

#include <algorithm>

namespace DoomMan {

Leaderboard::Leaderboard(const std::vector<PlayerState>& players) {
    std::vector<PlayerState> ranked(players.begin(), players.end());
    std::sort(ranked.begin(), ranked.end(),
              [](const PlayerState& a, const PlayerState& b) { return a.score > b.score; });

    int place = 1;
    for (const auto& player : ranked) {
        m_entries.push_back({place++, player.name, player.score});
    }
}

const std::vector<ScoreEntry>& Leaderboard::entries() const {
    return m_entries;
}

}  // namespace DoomMan
