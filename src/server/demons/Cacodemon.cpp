#include "server/demons/Cacodemon.h"

namespace Doom {

void Cacodemon::move(int deltaMs, const GameState& state, const PlayerState& target) {
    m_timeAccumulator += deltaMs;
    if (m_timeAccumulator < m_moveIntervalMs) return;
    m_timeAccumulator = 0;

    // Always randomly move for cacodemon
    performRandomFlee(state);
}
}  // namespace Doom