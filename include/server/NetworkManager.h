#pragma once

#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "common/Types.h"

namespace Doom {

class NetworkManager : public QObject {
    Q_OBJECT
   public:
    explicit NetworkManager(quint16 port, QObject* parent = nullptr);
    virtual ~NetworkManager();

   public slots:
    void broadcastState(const GameState& state);

   private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

   private:
    QTcpServer* m_server;
    QList<QTcpSocket*> m_clients;
};

}  // namespace Doom