#include "client/NetworkManager.h"
#include "common/Serialization.h"

#include <QDataStream>

namespace Doom {

ClientNetworkManager::ClientNetworkManager(QObject* parent)
    : QObject(parent), m_socket(new QTcpSocket(this)) {
    
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientNetworkManager::onReadyRead);
    
    connect(m_socket, &QTcpSocket::errorOccurred, [](QAbstractSocket::SocketError error) {
        qCritical() << "Network Error:" << error;
    });
}

void ClientNetworkManager::connectToServer(const QString& host, quint16 port) {
    m_socket->connectToHost(host, port);
}

void ClientNetworkManager::onReadyRead() {
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_6_0);

    in.startTransaction();

    GameState newState;
    
    in >> newState;

    if (in.commitTransaction()) {
        emit gameStateReceived(newState);
    } else {
        qDebug() << "Waiting for more data to complete GameState packet...";
    }
}

}  // namespace Doom