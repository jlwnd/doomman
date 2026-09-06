#include "client/ClientGameModel.h"

namespace DoomMan {

void ClientGameModel::setLocalNick(const QString& nick) {
    m_localNick = nick;
}

void ClientGameModel::update(const GameState& state) {
    m_state = state;
}

const GameState& ClientGameModel::state() const {
    return m_state;
}

std::optional<PlayerState> ClientGameModel::localPlayer() const {
    for (const auto& player : m_state.players) {
        if (player.name == m_localNick) return player;
    }
    return std::nullopt;
}

uint32_t ClientGameModel::localScore() const {
    const auto me = localPlayer();
    return me ? me->score : 0;
}

bool ClientGameModel::isLocalPlayerDead() const {
    const auto me = localPlayer();
    return me && !me->isAlive;
}

bool ClientGameModel::isInGame() const {
    return m_state.mode == GameMode::InGame;
}

Leaderboard ClientGameModel::leaderboard() const {
    return Leaderboard(m_state.players);
}

}  // namespace DoomMan
