#pragma once

#include <optional>
#include <string>

#include "common/Types.h"

namespace DoomMan {

/// Statyczna klasa pomocnicza wczytująca plansze z plików tekstowych.
class MapLoader {
   public:
    /// Wczytuje planszę z pliku i buduje na jej podstawie stan gry.
    /// @param filePath Ścieżka do pliku z planszą.
    /// @return Zainicjowany GameState lub std::nullopt przy błędzie odczytu.
    static std::optional<GameState> loadMap(const std::string& filePath);

   private:
    static TileType charToTile(char c);
};

}  // namespace DoomMan
