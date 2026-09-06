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
    container->setFixedSize(500, 400);

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

    m_startButton = new QPushButton("START", container);
    m_startButton->setObjectName("LobbyButton");
    m_startButton->setEnabled(false);

    containerLayout->addWidget(titleLabel);
    containerLayout->addWidget(m_playerList);
    containerLayout->addWidget(btnReady, 0, Qt::AlignHCenter);
    containerLayout->addWidget(m_startButton, 0, Qt::AlignHCenter);

    lobbyLayout->addWidget(container);

    setStyleSheet(R"(
        #LobbyContainer {
            background-color: #0b0c10;
            border: 2px solid #29b6f6;
            border-radius: 15px;
        }
        #TitleLabel {
            color: #ef5350;
            font-size: 48px;
            font-weight: bold;
            font-family: "Courier New", monospace;
        }
        #PlayerList {
            color: #ef5350;
            font-size: 18px;
            font-family: "Courier New", monospace;
            background: transparent;
            border: none;
        }
        #LobbyButton {
            color: #ef5350;
            font-size: 20px;
            font-family: "Courier New", monospace;
            background-color: transparent;
            border: none;
            padding: 5px;
        }
        #LobbyButton:hover:enabled {
            color: #ffffff;
        }
        #LobbyButton:disabled {
            color: #4a4a4a;
        }
    )");

    connect(btnReady, &QPushButton::clicked, this, &LobbyWidget::sigGameReady);
    connect(m_startButton, &QPushButton::clicked, this, &LobbyWidget::sigGameStart);
}

void LobbyWidget::setHost(bool isHost) {
    m_startButton->setEnabled(isHost);
}

void LobbyWidget::updateLobby(const GameState& state) {
    m_playerList->clear();
    for (const auto& player : state.players) {
        const QString prefix = player.isReady ? "[gotowy] " : "[niegotowy] ";
        m_playerList->addItem(prefix + player.name);
    }
}
}  // namespace DoomMan
