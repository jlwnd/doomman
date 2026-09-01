#pragma once
#include "server/demons/DemonBase.h"

namespace DoomMan {
/// Demon Imp – zawsze goni najbliższego gracza.
class Imp : public DemonBase {
   public:
    /// Tworzy demona Imp.
    /// @param type Typ demona.
    /// @param startPos Pozycja startowa.
    explicit Imp(DemonType type, Position startPos) : DemonBase(type, startPos, 400) {}

    /// Wykonuje ruch pościgu w kierunku celu.
    /// @param deltaMs Czas od poprzedniej klatki (ms).
    /// @param state Aktualny stan gry.
    /// @param target Gracz obrany za cel.
    void move(int deltaMs, const GameState& state, const PlayerState& target) override;
};
}  // namespace DoomMan