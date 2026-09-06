#pragma once

#include <QString>
#include <cstdint>
#include <optional>

#include "client/Leaderboard.h"
#include "common/Types.h"

namespace DoomMan {
/// Model rozgrywki po stronie klienta.
/// Przechowuje ostatni stan odebrany z serwera i udostępnia metody
/// pomocnicze, dzięki czemu widżety nie operują wprost na surowym GameState.
class ClientGameModel {
   public:
    /// Ustawia pseudonim gracza lokalnego (do rozpoznania "swojego" gracza).
    /// @param nick Pseudonim wysłany przy dołączaniu do gry.
    void setLocalNick(const QString& nick);

    /// Zapisuje najnowszy stan gry odebrany z serwera.
    /// @param state Stan gry z ostatniej klatki.
    void update(const GameState& state);

    /// @return Ostatni znany stan gry.
    const GameState& state() const;

    /// @return Stan gracza lokalnego, o ile jest obecny w rozgrywce.
    std::optional<PlayerState> localPlayer() const;

    /// @return Wynik gracza lokalnego (0, jeśli brak).
    uint32_t localScore() const;

    /// @return true, jeśli gracz lokalny jest obecny i zginął.
    bool isLocalPlayerDead() const;

    /// @return true, jeśli trwa rozgrywka.
    bool isInGame() const;

    /// @return Ranking wszystkich graczy z bieżącego stanu.
    Leaderboard leaderboard() const;

   private:
    GameState m_state;
    QString m_localNick;
};
}  // namespace DoomMan
