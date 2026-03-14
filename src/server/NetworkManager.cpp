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
        m_clients.append(client);

        connect(client, &QTcpSocket::disconnected, this, &NetworkManager::onClientDisconnected);
        connect(client, &QTcpSocket::readyRead, this, &NetworkManager::onReadyRead);

        qDebug() << "NetworkManager: Client connected from" << client->peerAddress().toString();
    }
}

void NetworkManager::onClientDisconnected() {
    auto* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        m_clients.removeAll(client);
        client->deleteLater();
        qDebug() << "NetworkManager: Client disconnected";
    }
}

void NetworkManager::onReadyRead() {
    auto* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        QByteArray data = client->readAll();
    }
}

void NetworkManager::broadcastState(const GameState& state) {
    if (m_clients.isEmpty()) return;

    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_0);

    stream << state;

    for (QTcpSocket* client : m_clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(packet);
        }
    }
}

}  // namespace Doom