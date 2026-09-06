#include "client/widgets/GameOverWidget.h"

#include <algorithm>

#include <QFrame>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace DoomMan {
GameOverWidget::GameOverWidget(QWidget* parent) : QWidget(parent) {
    auto* outerLayout = new QVBoxLayout(this);
    outerLayout->setAlignment(Qt::AlignCenter);

    auto* container = new QFrame(this);
    container->setObjectName("GameOverContainer");
    container->setFixedSize(500, 400);

    auto* containerLayout = new QVBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    containerLayout->setSpacing(25);
    containerLayout->setContentsMargins(0, 50, 0, 50);

    auto* titleLabel = new QLabel("KONIEC GRY", container);
    titleLabel->setObjectName("TitleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    m_scoreList = new QListWidget(container);
    m_scoreList->setObjectName("ScoreList");
    m_scoreList->setFocusPolicy(Qt::NoFocus);
    m_scoreList->setSelectionMode(QAbstractItemView::NoSelection);

    auto* exitButton = new QPushButton("WYJDŹ", container);
    exitButton->setObjectName("GameOverButton");

    containerLayout->addWidget(titleLabel);
    containerLayout->addWidget(m_scoreList);
    containerLayout->addWidget(exitButton, 0, Qt::AlignHCenter);

    outerLayout->addWidget(container);

    setStyleSheet(R"(
        #GameOverContainer {
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
        #ScoreList {
            color: #ef5350;
            font-size: 18px;
            font-family: "Courier New", monospace;
            background: transparent;
            border: none;
        }
        #GameOverButton {
            color: #ef5350;
            font-size: 20px;
            font-family: "Courier New", monospace;
            background-color: transparent;
            border: none;
            padding: 5px;
        }
        #GameOverButton:hover {
            color: #ffffff;
        }
    )");

    connect(exitButton, &QPushButton::clicked, this, &GameOverWidget::sigExit);
}

void GameOverWidget::showScores(const GameState& state) {
    std::vector<PlayerState> ranked(state.players.begin(), state.players.end());
    std::sort(ranked.begin(), ranked.end(),
              [](const PlayerState& a, const PlayerState& b) { return a.score > b.score; });

    m_scoreList->clear();
    int place = 1;
    for (const auto& player : ranked) {
        m_scoreList->addItem(QString("%1. %2 - %3").arg(place++).arg(player.name).arg(player.score));
    }
}
}  // namespace DoomMan
