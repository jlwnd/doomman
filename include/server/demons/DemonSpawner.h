#pragma once

#include <memory>

#include "common/Types.h"
#include "server/Demon.h"

namespace DoomMan {

/// Zarządza cyklem życia jednego demona: usuwa go po eliminacji
/// i odradza po upływie zadanego czasu.
class DemonSpawner {
   public:
    /// Tworzy spawner dla demona danego typu w zadanym punkcie.
    /// @param type Typ demona.
    /// @param spawnPos Punkt odrodzenia.
    DemonSpawner(DemonType type, Position spawnPos);

    /// Aktualizuje odliczanie do odrodzenia i ruch podległego demona.
    /// @param deltaMs Czas od poprzedniej klatki (ms).
    void update(int deltaMs);

    /// Zgłasza eliminację demona i uruchamia odliczanie do odrodzenia.
    void notifyDemonDeath();

    /// @return Wskaźnik do aktualnie żywego demona lub nullptr, jeśli martwy.
    Demon* getDemon() const;

    /// @return Punkt odrodzenia demona.
    Position getSpawnPos() const {
        return m_spawnPos;
    }

    /// @return Typ zarządzanego demona.
    DemonType getType() const {
        return m_type;
    }

   private:
    DemonType m_type;
    Position m_spawnPos;

    std::unique_ptr<Demon> m_demon;
    bool m_isAlive = true;
    int m_respawnTimerMs = 0;
    static constexpr int RESPAWN_DELAY_MS = 15000;
};

}  // namespace DoomMan
