#pragma once

#include <optional>
#include <string>
#include <vector>

#include "common/Types.h"

namespace DoomMan {

/// Wczytana plansza: stan gry (bez graczy) oraz punkty startowe z mapy.
struct LoadedLevel {
    GameState state;                ///< Stan gry z ustawioną planszą, bez graczy.
    std::vector<Position> spawns;   ///< Pozycje pól 'P' – po jednej na gracza.
};

/// Statyczna klasa pomocnicza wczytująca plansze z plików tekstowych.
class MapLoader {
   public:
    /// Wczytuje planszę z pliku i buduje na jej podstawie stan gry.
    /// @param filePath Ścieżka do pliku z planszą.
    /// @return Wczytana plansza z punktami startowymi lub std::nullopt przy błędzie odczytu.
    static std::optional<LoadedLevel> loadMap(const std::string& filePath);

   private:
    static TileType charToTile(char c);
};

}  // namespace DoomMan
