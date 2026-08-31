#include "server/ServerNetworkManager.h"

#include <QDataStream>
#include <QDebug>

#include "common/Protocol.h"
#include "common/Serialization.h"

namespace DoomMan {

ServerNetworkManager::ServerNetworkManager(quint16 port, QObject* parent)
    : QObject(parent), m_server(new QTcpServer(this)) {
    connect(m_server, &QTcpServer::newConnection, this, &ServerNetworkManager::onNewConnection);

    if (m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "[NetworkManager]: TCP Server started on port" << port;
    } else {
        qCritical() << "[NetworkManager]: Failed to start server on port" << port;
    }
}

ServerNetworkManager::~ServerNetworkManager() = default;

void ServerNetworkManager::onNewConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket* client = m_server->nextPendingConnection();
        uint32_t assignedId = m_nextPlayerId++;
        m_clientToPlayerId[client] = assignedId;

        connect(client, &QTcpSocket::disconnected, this,
                &ServerNetworkManager::onClientDisconnected);
        connect(client, &QTcpSocket::readyRead, this, &ServerNetworkManager::onReadyRead);

        qDebug() << "[NetworkManager]: Client connected. Assigned ID:" << assignedId;
    }
}

void ServerNetworkManager::onClientDisconnected() {
    auto* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        m_clientToPlayerId.remove(client);
        client->deleteLater();
        qDebug() << "[ServerNetworkManager]: Client disconnected";
    }
}

void ServerNetworkManager::onReadyRead() {
    auto* client = qobject_cast<QTcpSocket*>(sender());
    if (!client || !m_clientToPlayerId.contains(client)) return;

    QDataStream in(client);
    in.setVersion(QDataStream::Qt_6_0);

    while (!in.atEnd()) {
        in.startTransaction();
        PacketType type;
        in >> type;

        switch (type) {
            case PacketType::JoinRequest: {
                QString nick;
                in >> nick;

                if (!in.commitTransaction()) {
                    return;
                }

                emit joinRequested(m_clientToPlayerId[client], nick);
                break;
            }
            case PacketType::PlayerInput: {
                PlayerInput input;
                in >> input;

                if (!in.commitTransaction()) {
                    return;
                }

                emit inputReceived(m_clientToPlayerId[client], input);
                break;
            }
            default:
                in.abortTransaction();
                return;
        }
    }
}

void ServerNetworkManager::broadcastState(const GameState& state) {
    if (m_clientToPlayerId.isEmpty()) return;

    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_0);

    stream << state;

    for (auto it = m_clientToPlayerId.keyBegin(); it != m_clientToPlayerId.keyEnd(); ++it) {
        QTcpSocket* client = *it;
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(packet);
        }
    }
}

}  // namespace DoomMan