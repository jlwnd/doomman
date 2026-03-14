#include "server/NetworkManager.h"

#include <QDataStream>
#include <QDebug>

#include "common/Serialization.h"

namespace Doom {

NetworkManager::NetworkManager(quint16 port, QObject* parent)
    : QObject(parent), m_server(new QTcpServer(this)) {
    connect(m_server, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);

    if (m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "NetworkManager: TCP Server started on port" << port;
    } else {
        qCritical() << "NetworkManager: Failed to start server on port" << port;
    }
}

NetworkManager::~NetworkManager() = default;

void NetworkManager::onNewConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket* client = m_server->nextPendingConnection();
        uint32_t assignedId = m_nextPlayerId++;
        m_clientToPlayerId[client] = assignedId;

        connect(client, &QTcpSocket::disconnected, this, &NetworkManager::onClientDisconnected);
        connect(client, &QTcpSocket::readyRead, this, &NetworkManager::onReadyRead);

        qDebug() << "NetworkManager: Client connected. Assigned ID:" << assignedId;
    }
}

void NetworkManager::onClientDisconnected() {
    auto* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        m_clientToPlayerId.remove(client);
        client->deleteLater();
        qDebug() << "NetworkManager: Client disconnected";
    }
}

void NetworkManager::onReadyRead() {
    auto* client = qobject_cast<QTcpSocket*>(sender());
    if (!client || !m_clientToPlayerId.contains(client)) return;

    QDataStream in(client);
    in.setVersion(QDataStream::Qt_6_0);

    while (!in.atEnd()) {
        PlayerInput input;
        in >> input;
        emit inputReceived(m_clientToPlayerId[client], input);
    }
}

void NetworkManager::broadcastState(const GameState& state) {
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

}  // namespace Doom