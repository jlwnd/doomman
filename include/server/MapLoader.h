#pragma once

#include <optional>
#include <string>

#include "common/Types.h"

namespace Doom {

class MapLoader {
   public:
    static std::optional<GameState> loadMap(const std::string& filePath);

   private:
    static TileType charToTile(char c);
};

}  // namespace Doom