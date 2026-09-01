#pragma once
#include <random>

#include "server/demons/DemonBase.h"

namespace DoomMan {
/// Demon Cacodemon – porusza się chaotycznie, trudny do przewidzenia.
class Cacodemon : public DemonBase {
   public:
    /// Tworzy demona Cacodemon.
    /// @param type Typ demona.
    /// @param startPos Pozycja startowa.
    explicit Cacodemon(DemonType type, Position startPos)
        : DemonBase(type, startPos, 500), m_gen(std::random_device{}()) {}

    /// Wykonuje losowy ruch w dozwolonym kierunku.
    /// @param deltaMs Czas od poprzedniej klatki (ms).
    /// @param state Aktualny stan gry.
    /// @param target Gracz obrany za cel (dla tego demona pomijany).
    void move(int deltaMs, const GameState& state, const PlayerState& target) override;

   private:
    std::mt19937 m_gen;
};
}  // namespace DoomMan