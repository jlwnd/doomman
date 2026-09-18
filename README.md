<div align="center">
  <img src="https://github.com/jlwnd/doomman/blob/main/assets/textures/logo.png" alt="DoomMan Logo" width="256" height="256" style="image-rendering: pixelated; image-rendering: crisp-edges; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.5);">
  
  <h1>DoomMan</h1>
</div>

**DoomMan** is a multiplayer client-server game written in C++ using the Qt6 framework. The project combines classic Pac-Man mechanics with the atmosphere and enemies of the Doom universe. Players compete on a grid, collect ammo, evade demons with distinct behavior patterns, and utilize power-ups (Berserk) to score points. The game supports both human players over a network connection and AI bots.

## Requirements

To build and run the project properly, your system must have:

- A compiler supporting the **C++23** standard (e.g., GCC, Clang, MSVC)
- **CMake** version **3.20** or higher
- **Qt6** library (required modules: `Core`, `Widgets`, `Network`)
- _Optional:_ **Doxygen** (for generating documentation) and **Clang-Format** (for code formatting)

## Basic Commands

Project management is simplified via the included `Makefile`. Run the following commands in the project's root directory:

- **`make build`** (or `make all`)  
  Configures the project using CMake and compiles it into the `build/` directory.
- **`make run`**  
  Builds the project and launches the game client immediately.
- **`make test`**  
  Runs the unit test suite (grid logic, scoring, AI) via CTest.
- **`make clean`**  
  Removes the `build/` folder and generated binaries.
- **`make fmt`**  
  Formats the source code across all `.cpp` and `.h` files according to `.clang-format` rules.
- **`make generate-docs`**  
  Generates HTML documentation inside the `docs/doxygen/` directory (requires Doxygen to be installed).
