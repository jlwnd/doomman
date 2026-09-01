#pragma once
#include <QObject>
#include <QTcpSocket>

#include "common/Serialization.h"

namespace DoomMan {
/// Warstwa sieciowa klienta – utrzymuje połączenie z serwerem,
/// wysyła komendy ruchu i odbiera aktualizacje stanu gry.
class ClientNetworkManager : public QObject {
    Q_OBJECT
   public:
    /// Tworzy menedżera sieciowego klienta.
    /// @param parent Obiekt-rodzic Qt.
    explicit ClientNetworkManager(QObject* parent = nullptr);

    /// Łączy się z serwerem gry.
    /// @param host Adres hosta serwera.
    /// @param port Port TCP serwera.
    void connectToServer(const QString& host, quint16 port);

    /// Wysyła kierunek ruchu gracza do serwera.
    /// @param input Wciśnięty kierunek ruchu.
    void sendInput(PlayerInput input);

   signals:
    /// Emitowany po odebraniu i zdeserializowaniu stanu gry z serwera.
    /// @param state Odebrany stan gry.
    void gameStateReceived(const GameState& state);

   private slots:
    void onReadyRead();

   private:
    QTcpSocket* m_socket;
};
}  // namespace DoomMan
