#pragma once
#include "server/demons/DemonBase.h"

namespace DoomMan {
/// Demon Pinky – szybki demon próbujący zajść graczowi drogę.
class Pinky : public DemonBase {
   public:
    /// Tworzy demona Pinky.
    /// @param type Typ demona.
    /// @param startPos Pozycja startowa.
    explicit Pinky(DemonType type, Position startPos) : DemonBase(type, startPos, 250) {}

    /// Wykonuje ruch zmierzający do zablokowania drogi celowi.
    /// @param deltaMs Czas od poprzedniej klatki (ms).
    /// @param state Aktualny stan gry.
    /// @param target Gracz obrany za cel.
    void move(int deltaMs, const GameState& state, const PlayerState& target) override;
};
}  // namespace DoomMan