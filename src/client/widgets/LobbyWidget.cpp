#include "client/widgets/LobbyWidget.h"

#include <QFrame>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace DoomMan {
LobbyWidget::LobbyWidget(QWidget* parent) : QWidget(parent) {
    auto* lobbyLayout = new QVBoxLayout(this);
    lobbyLayout->setAlignment(Qt::AlignCenter);

    auto* container = new QFrame(this);
    container->setObjectName("LobbyContainer");
    container->setFixedSize(520, 560);

    auto* containerLayout = new QVBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    containerLayout->setSpacing(25);
    containerLayout->setContentsMargins(0, 50, 0, 50);

    auto* titleLabel = new QLabel("POCZEKALNIA", container);
    titleLabel->setObjectName("TitleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    m_playerList = new QListWidget(container);
    m_playerList->setObjectName("PlayerList");
    m_playerList->setFocusPolicy(Qt::NoFocus);
    m_playerList->setSelectionMode(QAbstractItemView::NoSelection);

    auto* btnReady = new QPushButton("GOTOWY", container);
    btnReady->setObjectName("LobbyButton");

    m_addBotButton = new QPushButton("DODAJ BOTA", container);
    m_addBotButton->setObjectName("LobbyButton");
    m_addBotButton->setEnabled(false);

    m_startButton = new QPushButton("START", container);
    m_startButton->setObjectName("LobbyButton");
    m_startButton->setEnabled(false);

    containerLayout->addWidget(titleLabel);
    containerLayout->addWidget(m_playerList);
    containerLayout->addWidget(btnReady, 0, Qt::AlignHCenter);
    containerLayout->addWidget(m_addBotButton, 0, Qt::AlignHCenter);
    containerLayout->addWidget(m_startButton, 0, Qt::AlignHCenter);

    lobbyLayout->addWidget(container);

    connect(btnReady, &QPushButton::clicked, this, &LobbyWidget::sigGameReady);
    connect(m_startButton, &QPushButton::clicked, this, &LobbyWidget::sigGameStart);
    connect(m_addBotButton, &QPushButton::clicked, this, &LobbyWidget::sigAddBot);
}

void LobbyWidget::setHost(bool isHost) {
    m_startButton->setEnabled(isHost);
    m_addBotButton->setEnabled(isHost);
}

void LobbyWidget::updateLobby(const GameState& state) {
    m_playerList->clear();
    for (const auto& player : state.players) {
        const QString prefix = player.isReady ? "[gotowy] " : "[niegotowy] ";
        m_playerList->addItem(prefix + player.name);
    }
}
}  // namespace DoomMan
