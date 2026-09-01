#pragma once

#include "common/Types.h"
#include "server/Demon.h"

namespace DoomMan {
/// Bazowa implementacja interfejsu Demon – wspólne atrybuty i zachowania
/// dziedziczone przez konkretne typy demonów.
class DemonBase : public Demon {
   public:
    /// Tworzy demona o zadanym typie, pozycji startowej i szybkości.
    /// @param type Typ demona.
    /// @param startPos Pozycja startowa na planszy.
    /// @param speed Odstęp między ruchami w ms (mniejszy = szybszy).
    explicit DemonBase(DemonType type, Position startPos, int speed)
        : m_pos(startPos), m_type(type), m_moveIntervalMs(speed) {}

    /// @return Aktualna pozycja demona.
    Position getPosition() const override;

    /// @return Typ demona.
    DemonType getType() const override;

    /// @return true, jeśli demon jest przerażony.
    bool isFrightened() const override;

    /// Ustawia stan przerażenia demona.
    /// @param f true, aby wprowadzić demona w tryb ucieczki.
    void setFrightened(bool f) override;

   protected:
    Position m_pos;             ///< Aktualna pozycja demona na planszy.
    DemonType m_type;           ///< Typ demona.
    bool m_frightened = false;  ///< Czy demon jest przerażony.
    int m_timeAccumulator = 0;  ///< Nagromadzony czas od ostatniego ruchu (ms).
    int m_moveIntervalMs;       ///< Odstęp między ruchami w ms (mniejszy = szybszy).

    /// Wykonuje jeden krok ucieczki w losowym, dozwolonym kierunku.
    /// @param state Aktualny stan gry.
    void performRandomFlee(const GameState& state);
};
}  // namespace DoomMan