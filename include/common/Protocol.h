#pragma once

/// @file
/// @brief Typy pakietów i nagłówek protokołu sieciowego klient–serwer.

#include <QDataStream>
#include <cstdint>

namespace DoomMan {

/// Typ pakietu wymienianego między klientem a serwerem.
enum class PacketType : uint8_t {
    JoinRequest = 0,    ///< Prośba gracza o dołączenie do gry.
    LobbyUpdate = 1,    ///< Aktualizacja stanu lobby.
    PlayerReady = 2,    ///< Zgłoszenie gotowości gracza.
    GameStart = 3,      ///< Rozpoczęcie rundy.
    PlayerInput = 4,    ///< Wciśnięty przez gracza kierunek ruchu.
    GameStateSync = 5,  ///< Synchronizacja pełnego stanu gry.
    ChatMessage = 6,    ///< Wiadomość czatu.
    AddBot = 7          ///< Prośba hosta o dodanie gracza AI.
};

/// Nagłówek pakietu sieciowego określający jego typ.
struct NetworkPacket {
    PacketType type;  ///< Rodzaj pakietu.
};

}  // namespace DoomMan