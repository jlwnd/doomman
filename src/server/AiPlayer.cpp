#include "server/AiPlayer.h"

#include <array>
#include <queue>

#include "common/Tiles.h"
#include "common/Types.h"
#include "server/Navigation.h"

namespace DoomMan {

PlayerInput AiPlayer::decideMove(const GameState& state) const {
    PlayerState aiPlayer = findPlayerWithId(state, m_playerId);

    if (!aiPlayer.id) {
        return PlayerInput::None;
    }

    Position closestValuableTarget = findClosestValuableTarget(state, aiPlayer.pos);

    if (closestValuableTarget == aiPlayer.pos) {
        return PlayerInput::None;
    }

    return Navigation::getNextMoveAStar(aiPlayer.pos, closestValuableTarget, state.board.tiles());
};

Position AiPlayer::findClosestValuableTarget(const GameState& state,
                                             const Position currentPos) const {
    const Map& board = state.board;
    std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> visited{};
    std::queue<Position> frontier;

    frontier.push(currentPos);
    visited[currentPos.y][currentPos.x] = true;

    while (!frontier.empty()) {
        const Position cur = frontier.front();
        frontier.pop();

        if (cur != currentPos &&
            (board.at(cur) == TileType::Corridor || board.at(cur) == TileType::Berserk)) {
            return cur;
        }

        const Position neighbours[4] = {
            {cur.x + 1, cur.y}, {cur.x - 1, cur.y}, {cur.x, cur.y + 1}, {cur.x, cur.y - 1}};

        for (const Position n : neighbours) {
            if (!board.isBounds(n) || visited[n.y][n.x] || board.isWall(n)) {
                continue;
            }
            visited[n.y][n.x] = true;
            frontier.push(n);
        }
    }

    return currentPos;
};

PlayerState AiPlayer::findPlayerWithId(const GameState& state, const uint32_t playerId) const {
    for (auto& player : state.players) {
        if (player.isAlive && player.id == playerId) {
            return player;
        }
    }
    return PlayerState{};
}
}  // namespace DoomMan
