#include "client/widgets/MainMenuWidget.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace DoomMan {

MainMenuWidget::MainMenuWidget(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    auto* container = new QFrame(this);
    container->setObjectName("MenuContainer");
    container->setFixedSize(520, 560);

    auto* containerLayout = new QVBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    containerLayout->setSpacing(25);
    containerLayout->setContentsMargins(0, 50, 0, 50);

    auto* titleLabel = new QLabel("DOOMMAN", container);
    titleLabel->setObjectName("TitleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    auto* nickLayout = new QHBoxLayout();
    nickLayout->setAlignment(Qt::AlignCenter);
    auto* nickLabel = new QLabel("NICK:", container);
    nickLabel->setObjectName("NickLabel");
    m_nickEdit = new QLineEdit(container);
    m_nickEdit->setObjectName("NickEdit");
    m_nickEdit->setFixedWidth(200);

    nickLayout->addWidget(nickLabel);
    nickLayout->addWidget(m_nickEdit);

    auto* hostLayout = new QHBoxLayout();
    hostLayout->setAlignment(Qt::AlignCenter);
    auto* hostLabel = new QLabel("IP HOSTA:", container);
    hostLabel->setObjectName("NickLabel");
    m_hostEdit = new QLineEdit("127.0.0.1", container);
    m_hostEdit->setObjectName("NickEdit");
    m_hostEdit->setFixedWidth(200);

    hostLayout->addWidget(hostLabel);
    hostLayout->addWidget(m_hostEdit);

    auto* btnHost = new QPushButton("HOST GRY", container);
    auto* btnJoin = new QPushButton("DOŁĄCZ DO GRY", container);
    auto* btnExit = new QPushButton("WYJŚCIE", container);

    btnHost->setObjectName("MenuButton");
    btnJoin->setObjectName("MenuButton");
    btnExit->setObjectName("MenuButton");

    containerLayout->addWidget(titleLabel);
    containerLayout->addLayout(nickLayout);
    containerLayout->addLayout(hostLayout);
    containerLayout->addSpacing(20);
    containerLayout->addWidget(btnHost, 0, Qt::AlignHCenter);
    containerLayout->addWidget(btnJoin, 0, Qt::AlignHCenter);
    containerLayout->addWidget(btnExit, 0, Qt::AlignHCenter);

    mainLayout->addWidget(container);

    connect(btnHost, &QPushButton::clicked, this, &MainMenuWidget::onHostClicked);
    connect(btnJoin, &QPushButton::clicked, this, &MainMenuWidget::onJoinClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainMenuWidget::onExitClicked);
}

void MainMenuWidget::onHostClicked() {
    emit sigHostGame(m_nickEdit->text());
}

void MainMenuWidget::onJoinClicked() {
    emit sigJoinGame(m_nickEdit->text(), m_hostEdit->text());
}

void MainMenuWidget::onExitClicked() {
    emit sigExit();
}

}  // namespace DoomMan
