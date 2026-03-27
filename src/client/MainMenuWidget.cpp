#include "client/MainMenuWidget.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace Doom {

MainMenuWidget::MainMenuWidget(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    auto* container = new QFrame(this);
    container->setObjectName("MenuContainer");
    container->setFixedSize(500, 400);

    auto* containerLayout = new QVBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    containerLayout->setSpacing(25);
    containerLayout->setContentsMargins(0, 50, 0, 50);

    auto* titleLabel = new QLabel("DOOM", container);
    titleLabel->setObjectName("TitleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    auto* nickLayout = new QHBoxLayout();
    nickLayout->setAlignment(Qt::AlignCenter);
    auto* nickLabel = new QLabel("NICK:", container);
    nickLabel->setObjectName("NickLabel");
    m_nickEdit = new QLineEdit(container);
    m_nickEdit->setObjectName("NickEdit");
    m_nickEdit->setFixedWidth(150);

    nickLayout->addWidget(nickLabel);
    nickLayout->addWidget(m_nickEdit);

    auto* btnHost = new QPushButton("HOST GRY", container);
    auto* btnJoin = new QPushButton("DOŁĄCZ DO GRY", container);
    auto* btnExit = new QPushButton("WYJŚCIE", container);

    btnHost->setObjectName("MenuButton");
    btnJoin->setObjectName("MenuButton");
    btnExit->setObjectName("MenuButton");

    containerLayout->addWidget(titleLabel);
    containerLayout->addLayout(nickLayout);
    containerLayout->addSpacing(20);
    containerLayout->addWidget(btnHost, 0, Qt::AlignHCenter);
    containerLayout->addWidget(btnJoin, 0, Qt::AlignHCenter);
    containerLayout->addWidget(btnExit, 0, Qt::AlignHCenter);

    mainLayout->addWidget(container);

    // @TODO: Change styling
    setStyleSheet(R"(
        #MenuContainer {
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
        #NickLabel, #NickEdit {
            color: #ef5350;
            font-size: 20px;
            font-family: "Courier New", monospace;
            background: transparent;
            border: none;
        }
        #NickEdit {
            border-bottom: 2px dashed #ef5350;
        }
        #MenuButton {
            color: #ef5350;
            font-size: 20px;
            font-family: "Courier New", monospace;
            background-color: transparent;
            border: none;
            padding: 5px;
        }
        #MenuButton:hover {
            color: #ffffff;
        }
    )");

    connect(btnHost, &QPushButton::clicked, this, &MainMenuWidget::onHostClicked);
    connect(btnJoin, &QPushButton::clicked, this, &MainMenuWidget::onJoinClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainMenuWidget::onExitClicked);
}

void MainMenuWidget::onHostClicked() {
    emit sigHostGame(m_nickEdit->text());
}

void MainMenuWidget::onJoinClicked() {
    emit sigJoinGame(m_nickEdit->text());
}

void MainMenuWidget::onExitClicked() {
    emit sigExit();
}

}  // namespace Doom
