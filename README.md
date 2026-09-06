<div align="center">
  <img src="https://github.com/jlwnd/doomman/blob/main/assets/textures/logo.png" alt="DoomMan Logo" width="256" height="256" style="image-rendering: pixelated; image-rendering: crisp-edges; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.5);"">
  
  <h1>DoomMan</h1>
</div>

**DoomMan** to wieloosobowa gra typu klient-serwer napisana w C++ (z wykorzystaniem frameworka Qt6). Projekt łączy klasyczne mechaniki Pac-Mana z klimatem i przeciwnikami ze świata Dooma. Gracze rywalizują na planszy, zbierają amunicję, unikają demonów o różnych wzorcach zachowań i używają power-upów (Berserk), aby zdobywać punkty. Gra obsługuje zarówno żywych graczy przez sieć, jak i boty AI.

## Wymagania

Aby poprawnie skompilować i uruchomić projekt, Twój system musi posiadać:

- Kompilator obsługujący standard **C++23** (np. GCC, Clang, MSVC)
- **CMake** w wersji **3.20** lub nowszej
- Bibliotekę **Qt6** (wymagane komponenty: `Core`, `Widgets`, `Network`)
- _Opcjonalnie:_ **Doxygen** (do generowania dokumentacji) oraz **Clang-Format** (do formatowania kodu)

## Podstawowe komendy

Zarządzanie projektem jest uproszczone dzięki dołączonemu plikowi `Makefile`. Uruchom poniższe komendy w głównym katalogu projektu:

- **`make build`** (lub `make all`)
  Konfiguruje projekt przy użyciu CMake i kompiluje go do folderu `build/`.
- **`make run`** Buduje projekt i natychmiast uruchamia klienta gry.
- **`make test`** Uruchamia zestaw testów jednostkowych (logika siatki, punktacja, AI) za pomocą CTest.
- **`make clean`** Usuwa folder `build/` oraz wygenerowane pliki binarne.
- **`make fmt`** Formatuje kod źródłowy we wszystkich plikach `.cpp` i `.h` według reguł z `.clang-format`.
- **`make generate-docs`** Generuje dokumentację w formacie HTML w katalogu `docs/doxygen/` (wymaga zainstalowanego Doxygen).
