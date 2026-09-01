#pragma once

#include "common/Types.h"

namespace DoomMan {

/// Czysto wirtualny interfejs demona.
/// Definiuje wspólny zestaw operacji dla wszystkich typów AI.
class Demon {
   public:
    virtual ~Demon() = default;

    /// Aktualizuje pozycję demona zgodnie z jego algorytmem AI.
    /// @param deltaMs Czas, jaki upłynął od poprzedniej klatki (ms).
    /// @param state Aktualny stan gry.
    /// @param target Gracz obrany za cel.
    virtual void move(int deltaMs, const GameState& state, const PlayerState& target) = 0;

    /// @return Aktualna pozycja demona na planszy.
    virtual Position getPosition() const = 0;

    /// @return Typ demona.
    virtual DemonType getType() const = 0;

    /// @return true, jeśli demon jest przerażony.
    virtual bool isFrightened() const = 0;

    /// Ustawia stan przerażenia demona.
    /// @param f true, aby wprowadzić demona w tryb ucieczki.
    virtual void setFrightened(bool f) = 0;
};
}  // namespace DoomMan