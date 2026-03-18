#pragma once

#include <memory>
#include "common/Types.h"
#include "server/Demon.h"

namespace Doom {

class DemonSpawner {
   public:
    DemonSpawner(DemonType type, Position spawnPos);

    void update(int deltaMs);

    void notifyDemonDeath();

    Demon* getDemon() const;

    Position getSpawnPos() const { return m_spawnPos; }
    DemonType getType() const { return m_type; }

   private:
    DemonType m_type;
    Position m_spawnPos;

    std::unique_ptr<Demon> m_demon;
    bool m_isAlive = true;
    int m_respawnTimerMs = 0;
    static constexpr int RESPAWN_DELAY_MS = 15000;
};

}  // namespace Doom
