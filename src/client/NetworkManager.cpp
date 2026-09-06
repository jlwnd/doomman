#include "client/NetworkManager.h"

#include <QDataStream>

#include "common/Protocol.h"
#include "common/Serialization.h"

namespace DoomMan {

ClientNetworkManager::ClientNetworkManager(QObject* parent)
    : QObject(parent), m_socket(new QTcpSocket(this)) {
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientNetworkManager::onReadyRead);

    connect(m_socket, &QTcpSocket::errorOccurred, this, &ClientNetworkManager::onSocketError);

    connect(m_socket, &QTcpSocket::connected, this, &ClientNetworkManager::sendJoin);
}

void ClientNetworkManager::connectToServer(const QString& host, quint16 port, const QString& nick) {
    m_nick = nick;
    m_socket->connectToHost(host, port);
}

void ClientNetworkManager::sendJoin() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << PacketType::JoinRequest << m_nick;
    m_socket->write(block);
}

void ClientNetworkManager::onReadyRead() {
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_6_0);

    in.startTransaction();

    GameState newState;

    in >> newState;

    if (in.commitTransaction()) {
        emit gameStateReceived(newState);
    }
}

void ClientNetworkManager::onSocketError(QAbstractSocket::SocketError error) {
    qCritical() << "Network Error:" << error;
}

void ClientNetworkManager::sendInput(PlayerInput input) {
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << PacketType::PlayerInput << input;
    m_socket->write(block);
}

void ClientNetworkManager::sendReady() {
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << PacketType::PlayerReady;
    m_socket->write(block);
}

void ClientNetworkManager::sendStart() {
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << PacketType::GameStart;
    m_socket->write(block);
}

void ClientNetworkManager::sendAddBot() {
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << PacketType::AddBot;
    m_socket->write(block);
}

}  // namespace DoomMan
