#pragma once

#include <common/Map.h>

#include <QString>
#include <array>
#include <compare>
#include <cstdint>
#include <string>
#include <vector>

namespace DoomMan {

/// Maksymalna liczba graczy w jednej rozgrywce.
inline constexpr int MAX_PLAYERS = 4;

/// Długość jednego kroku symulacji w ms (wspólna baza czasu dla silnika i AI).
inline constexpr int TICK_RATE_MS = 100;

/// Liczba demonów obecnych na planszy.
inline constexpr int DEMON_COUNT = 4;

/// Typ demona wyznaczający jego algorytm zachowania.
enum class DemonType : uint8_t {
    Imp,        ///< Goni najbliższego gracza.
    Pinky,      ///< Próbuje zajść graczowi drogę (przewiduje ruch).
    Cacodemon,  ///< Porusza się chaotycznie.
    LostSoul    ///< Patroluje sektor, atakuje gdy gracz wejdzie w zasięg.
};

/// Aktualna faza rozgrywki.
enum class GameMode : uint8_t {
    Lobby,   ///< Poczekalnia przed startem rundy.
    InGame,  ///< Trwająca rozgrywka.
    Summary  ///< Ekran podsumowania po zakończeniu rundy.
};

/// Kierunek ruchu wciśnięty przez gracza.
enum class PlayerInput : uint8_t {
    MoveUp,     ///< Ruch w górę.
    MoveDown,   ///< Ruch w dół.
    MoveLeft,   ///< Ruch w lewo.
    MoveRight,  ///< Ruch w prawo.
    None        ///< Brak ruchu.
};

/// Stan pojedynczego gracza w danej klatce rozgrywki.
struct PlayerState {
    uint32_t id = 0;                            ///< Unikalny identyfikator gracza.
    Position pos;                               ///< Aktualna pozycja na planszy.
    PlayerInput lastInput = PlayerInput::None;  ///< Ostatni odebrany kierunek ruchu.
    uint32_t score = 0;                         ///< Aktualny wynik punktowy.
    QString name;                               ///< Pseudonim gracza.
    bool isReady = false;                       ///< Czy gracz zgłosił gotowość w lobby.
    bool isAlive = true;                        ///< Czy gracz żyje.
    bool hasBerserk = false;                    ///< Czy gracz ma aktywny bonus Berserka.
};

/// Stan pojedynczego demona w danej klatce rozgrywki.
struct DemonState {
    DemonType type;             ///< Typ demona.
    Position pos;               ///< Aktualna pozycja na planszy.
    bool isFrightened = false;  ///< Czy demon jest przerażony (tryb ucieczki).
    bool isAlive = true;        ///< Czy demon żyje.
};

/// Centralny kontener pełnego stanu świata gry – źródło prawdy
/// przesyłane z serwera do klientów.
struct GameState {
    GameMode mode = GameMode::Lobby;             ///< Aktualna faza rozgrywki.
    Map board;                                   ///< Plansza (labirynt i kafelki).
    std::vector<PlayerState> players;            ///< Lista aktywnych graczy.
    std::array<DemonState, DEMON_COUNT> demons;  ///< Stany wszystkich demonów.
    int32_t timeLeftSeconds = 180;               ///< Pozostały czas rundy w sekundach.
};

}  // namespace DoomMan
