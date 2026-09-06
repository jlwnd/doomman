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

    /// Łączy się z serwerem gry i po nawiązaniu połączenia zgłasza dołączenie.
    /// @param host Adres hosta serwera.
    /// @param port Port TCP serwera.
    /// @param nick Pseudonim gracza wysyłany w prośbie o dołączenie.
    void connectToServer(const QString& host, quint16 port, const QString& nick);

    /// Wysyła kierunek ruchu gracza do serwera.
    /// @param input Wciśnięty kierunek ruchu.
    void sendInput(PlayerInput input);

    /// Zgłasza serwerowi gotowość gracza w lobby.
    void sendReady();

    /// Zgłasza serwerowi rozpoczęcie rundy (tylko host).
    void sendStart();

   signals:
    /// Emitowany po odebraniu i zdeserializowaniu stanu gry z serwera.
    /// @param state Odebrany stan gry.
    void gameStateReceived(const GameState& state);

   private slots:
    void onReadyRead();

   private:
    /// Wysyła do serwera prośbę o dołączenie z zapamiętanym pseudonimem.
    void sendJoin();

    QTcpSocket* m_socket;
    QString m_nick;  ///< Pseudonim wysyłany przy dołączaniu do gry.
};
}  // namespace DoomMan
