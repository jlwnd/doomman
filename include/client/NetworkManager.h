#pragma once
#include <QObject>
#include <QTcpSocket>

#include "common/Serialization.h"

namespace DoomMan {
class ClientNetworkManager : public QObject {
    Q_OBJECT
   public:
    explicit ClientNetworkManager(QObject* parent = nullptr);
    void connectToServer(const QString& host, quint16 port);
    void sendInput(PlayerInput input);

   signals:
    void gameStateReceived(const GameState& state);

   private slots:
    void onReadyRead();

   private:
    QTcpSocket* m_socket;
};
}  // namespace DoomMan
