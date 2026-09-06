#include <common/Types.h>
#include <server/GameEngine.h>

#include <cassert>
#include <cstdio>

using namespace DoomMan;

static GameState makeState(Position playerPos) {
    GameState s;
    PlayerState p;
    p.id = 1;
    p.pos = playerPos;
    s.players.push_back(p);
    return s;
}

static void test_pellet_scores() {
    GameState s = makeState({5, 3});
    s.board.set({5, 4}, TileType::Corridor);
    GameEngine engine{s};

    engine.processInput(1, PlayerInput::MoveDown);
    assert(s.players[0].score == 10);
    assert(s.board.at({5, 4}) == TileType::Empty);
}

static void test_demon_kill_scores() {
    GameState s = makeState({5, 3});
    s.board.set({5, 4}, TileType::Berserk);
    s.board.set({5, 5}, TileType::ImpSpawn);
    GameEngine engine{s};

    engine.processInput(1, PlayerInput::MoveDown);
    assert(s.players[0].hasBerserk);

    engine.processInput(1, PlayerInput::MoveDown);
    assert(s.players[0].score == 200);
    assert(!s.demons[0].isAlive);
}

static void test_escalating_berserk_scores() {
    GameState s = makeState({5, 2});
    s.board.set({5, 3}, TileType::Berserk);
    s.board.set({5, 4}, TileType::ImpSpawn);
    s.board.set({5, 5}, TileType::PinkySpawn);
    GameEngine engine{s};

    engine.processInput(1, PlayerInput::MoveDown);  // {5,3}: Berserk, chain = 0
    engine.processInput(1, PlayerInput::MoveDown);  // {5,4}: 1st demon -> +200
    engine.processInput(1, PlayerInput::MoveDown);  // {5,5}: 2nd demon -> +400
    assert(s.players[0].score == 600);
}

static void test_no_kill_without_berserk() {
    GameState s = makeState({5, 4});
    s.board.set({5, 5}, TileType::ImpSpawn);
    GameEngine engine{s};

    engine.processInput(1, PlayerInput::MoveDown);
    assert(s.players[0].score == 0);
    assert(s.demons[0].isAlive);
}

int main() {
    test_pellet_scores();
    test_demon_kill_scores();
    test_escalating_berserk_scores();
    test_no_kill_without_berserk();
    std::puts("all scoring tests passed");
    return 0;
}
