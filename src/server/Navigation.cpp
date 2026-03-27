#include "server/Navigation.h"

#include <algorithm>
#include <map>
#include <queue>
#include <set>

namespace DoomMan {
PlayerInput Navigation::getNextMoveAStar(
    const Position& start, const Position& target,
    const std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE>& board) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::map<Position, int> gScore;
    std::map<Position, Position> cameFrom;

    openSet.push({start, 0, distanceBetween(start, target), start});
    gScore[start] = 0;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.pos == target) {
            Position firstStep = target;

            while (!(cameFrom[firstStep] == start)) {
                firstStep = cameFrom[firstStep];
            }

            if (firstStep.x > start.x) return PlayerInput::MoveRight;
            if (firstStep.x < start.x) return PlayerInput::MoveLeft;
            if (firstStep.y > start.y) return PlayerInput::MoveDown;
            if (firstStep.y < start.y) return PlayerInput::MoveUp;
        }

        const Position possibleNeighbours[4] = {{current.pos.x, current.pos.y - 1},
                                                {current.pos.x, current.pos.y + 1},
                                                {current.pos.x - 1, current.pos.y},
                                                {current.pos.x + 1, current.pos.y}};

        for (const Position neighbour : possibleNeighbours) {
            if (neighbour.x < 0 || neighbour.y >= BOARD_SIZE || neighbour.y < 0 ||
                neighbour.y >= BOARD_SIZE)
                continue;
            if (board[neighbour.y][neighbour.x] == TileType::Wall) continue;

            int new_gScore = gScore[current.pos] + 1;
            if (!gScore.count(neighbour) || new_gScore < gScore[neighbour]) {
                cameFrom[neighbour] = current.pos;
                gScore[neighbour] = new_gScore;
                openSet.push(
                    {neighbour, new_gScore, distanceBetween(neighbour, target), current.pos});
            }
        }
    }

    return PlayerInput::None;
};

int Navigation::distanceBetween(const Position& start, const Position& currentPos) {
    return std::abs(start.x - currentPos.x) + std::abs(start.y - currentPos.y);
}

} // namespace DoomMan