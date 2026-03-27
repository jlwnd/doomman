#pragma once

#include <optional>
#include <string>

#include "common/Types.h"

namespace DoomMan {

class MapLoader {
   public:
    static std::optional<GameState> loadMap(const std::string& filePath);

   private:
    static TileType charToTile(char c);
};

} // namespace DoomMan