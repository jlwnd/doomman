#pragma once

#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "common/Types.h"

namespace DoomMan {

class ServerNetworkManager : public QObject {
    Q_OBJECT
   public:
    explicit ServerNetworkManager(quint16 port, QObject* parent = nullptr);
    virtual ~ServerNetworkManager();

   public slots:
    void broadcastState(const GameState& state);

   signals:
    void inputReceived(uint32_t playerId, PlayerInput input);
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