#include <common/Types.h>
#include <server/AiPlayer.h>

#include <cassert>
#include <cstdio>

using namespace DoomMan;

static GameState makeState(Position playerPos, bool alive = true) {
    GameState s;
    PlayerState p;
    p.id = 1;
    p.pos = playerPos;
    p.isAlive = alive;
    s.players.push_back(p);
    return s;
}

static void test_picks_nearest() {
    GameState s = makeState({5, 5});
    s.board.set({5, 7}, TileType::Corridor);
    s.board.set({8, 5}, TileType::Corridor);
    AiPlayer ai{1, 0};
    assert(ai.decideMove(TICK_RATE_MS, s) == PlayerInput::MoveDown);
}

static void test_avoids_walls() {
    GameState s = makeState({5, 5});
    s.board.set({6, 5}, TileType::Wall);
    s.board.set({7, 5}, TileType::Corridor);
    s.board.set({5, 7}, TileType::Corridor);
    AiPlayer ai{1, 0};
    assert(ai.decideMove(TICK_RATE_MS, s) == PlayerInput::MoveDown);
}

static void test_skips_current_tile() {
    GameState s = makeState({5, 5});
    s.board.set({5, 5}, TileType::Corridor);
    s.board.set({5, 7}, TileType::Corridor);
    AiPlayer ai{1, 0};
    assert(ai.decideMove(TICK_RATE_MS, s) == PlayerInput::MoveDown);
}

static void test_no_target_returns_none() {
    GameState s = makeState({5, 5});
    AiPlayer ai{1, 0};
    assert(ai.decideMove(TICK_RATE_MS, s) == PlayerInput::None);
}

static void test_dead_returns_none() {
    GameState s = makeState({5, 5}, /*alive=*/false);
    s.board.set({5, 7}, TileType::Corridor);
    AiPlayer ai{1, 0};
    assert(ai.decideMove(TICK_RATE_MS, s) == PlayerInput::None);
}

static void test_throttles_by_speed() {
    GameState s = makeState({5, 5});
    s.board.set({5, 7}, TileType::Corridor);
    AiPlayer ai{1, 200};  // ruch co 200 ms
    assert(ai.decideMove(100, s) == PlayerInput::None);      // 100 ms – za wcześnie
    assert(ai.decideMove(100, s) == PlayerInput::MoveDown);  // 200 ms – ruch
}

int main() {
    test_picks_nearest();
    test_avoids_walls();
    test_skips_current_tile();
    test_no_target_returns_none();
    test_dead_returns_none();
    test_throttles_by_speed();
    std::puts("test_aiplayer: OK");
    return 0;
}
