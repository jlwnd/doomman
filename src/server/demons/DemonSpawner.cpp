#include "server/demons/DemonSpawner.h"

#include "server/demons/Cacodemon.h"
#include "server/demons/Imp.h"
#include "server/demons/LostSoul.h"
#include "server/demons/Pinky.h"

namespace DoomMan {

namespace {
std::unique_ptr<Demon> createDemon(DemonType type, Position pos) {
    switch (type) {
        case DemonType::Imp:
            return std::make_unique<Imp>(type, pos);
        case DemonType::Pinky:
            return std::make_unique<Pinky>(type, pos);
        case DemonType::Cacodemon:
            return std::make_unique<Cacodemon>(type, pos);
        case DemonType::LostSoul:
            return std::make_unique<LostSoul>(type, pos);
    }
    return nullptr;
}
}  // namespace

DemonSpawner::DemonSpawner(DemonType type, Position spawnPos)
    : m_type(type), m_spawnPos(spawnPos), m_isAlive(true) {
    m_demon = createDemon(type, spawnPos);
}

void DemonSpawner::update(int deltaMs) {
    if (!m_isAlive) {
        m_respawnTimerMs -= deltaMs;
        if (m_respawnTimerMs <= 0) {
            m_demon = createDemon(m_type, m_spawnPos);
            m_isAlive = true;
            m_respawnTimerMs = 0;
        }
    }
}

void DemonSpawner::notifyDemonDeath() {
    m_isAlive = false;
    m_respawnTimerMs = RESPAWN_DELAY_MS;
    m_demon.reset();
}

Demon* DemonSpawner::getDemon() const {
    return m_demon.get();
}

} // namespace DoomMan
