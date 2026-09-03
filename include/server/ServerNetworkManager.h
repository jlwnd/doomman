#pragma once

#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "common/Types.h"

namespace DoomMan {

/// Zarządza połączeniami TCP klientów: odbiera pakiety wejść
/// i rozsyła zserializowany stan gry do wszystkich uczestników sesji.
class ServerNetworkManager : public QObject {
    Q_OBJECT
   public:
    /// Tworzy menedżera nasłuchującego na zadanym porcie.
    /// @param port Port TCP nasłuchu.
    /// @param parent Obiekt-rodzic Qt.
    explicit ServerNetworkManager(quint16 port, QObject* parent = nullptr);

    /// Zamyka serwer i zwalnia zasoby połączeń.
    virtual ~ServerNetworkManager();

    /// Rezerwuje kolejne unikalne id gracza – wspólne dla ludzi i botów.
    /// @return Nowe, niepowtarzalne id gracza.
    uint32_t allocatePlayerId() {
        return m_nextPlayerId++;
    }

   public slots:
    /// Rozsyła aktualny stan gry do wszystkich podłączonych klientów.
    /// @param state Stan gry do wysłania.
    void broadcastState(const GameState& state);

   signals:
    /// Emitowany po odebraniu kierunku ruchu od klienta.
    /// @param playerId Identyfikator gracza.
    /// @param input Odebrany kierunek ruchu.
    void inputReceived(uint32_t playerId, PlayerInput input);

    /// Emitowany po odebraniu prośby o dołączenie do gry.
    /// @param playerId Identyfikator nadany nowemu graczowi.
    /// @param nick Pseudonim gracza.
    void joinRequested(uint32_t playerId, const QString& nick);

   private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

   private:
    QTcpServer* m_server;
    QMap<QTcpSocket*, uint32_t> m_clientToPlayerId;
    uint32_t m_nextPlayerId = 0;
};

}  // namespace DoomMan