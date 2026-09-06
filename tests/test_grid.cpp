#include <common/Grid.h>

#include <cassert>
#include <cstdio>

using namespace DoomMan;

static void test_fill() {
    Grid<int, 5> g;
    g.fill(7);
    assert(g.at(0, 0) == 7);
    assert(g.at(4, 4) == 7);
}

static void test_at_readwrite() {
    Grid<int, 5> g;
    g.fill(0);
    g.at(2, 3) = 42;
    assert(g.at(2, 3) == 42);
    assert(g.at(3, 2) == 0);
}

static void test_inBounds() {
    Grid<int, 5> g;
    assert(g.inBounds(0, 0));
    assert(g.inBounds(4, 4));
    assert(!g.inBounds(5, 0));
    assert(!g.inBounds(-1, 0));
}

static void test_generic() {
    Grid<char, 3> g;
    g.fill('x');
    assert(g.at(1, 1) == 'x');
}

int main() {
    test_fill();
    test_at_readwrite();
    test_inBounds();
    test_generic();
    std::puts("all grid tests passed");
    return 0;
}