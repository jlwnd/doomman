#pragma once

#include <random>

#include "server/demons/DemonBase.h"

namespace DoomMan {
/// Demon Lost Soul – patroluje wyznaczony sektor wokół bazy,
/// atakuje gdy gracz wejdzie w zasięg agresji.
class LostSoul : public DemonBase {
   public:
    /// Tworzy demona Lost Soul.
    /// @param type Typ demona.
    /// @param startPos Pozycja startowa (jednocześnie środek patrolu).
    explicit LostSoul(DemonType type, Position startPos)
        : DemonBase(type, startPos, 600), m_homeBase(startPos), m_gen(std::random_device{}()) {}

    // Patroluje sektor lub goni cel, jeśli znalazł się w zasięgu agresji.
    /// @param deltaMs Czas od poprzedniej klatki (ms).
    /// @param state Aktualny stan gry.
    /// @param target Gracz obrany za cel.
    void move(int deltaMs, const GameState& state, const PlayerState& target) override;

   private:
    Position m_homeBase;
    const int AGGRO_RANGE = 6;
    const int PATROL_RADIUS = 4;
    std::mt19937 m_gen;
};

}  // namespace DoomMan