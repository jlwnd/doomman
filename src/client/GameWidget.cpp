#include "client/GameWidget.h"

#include <QPaintEvent>
#include <QPainter>

namespace DoomMan {

GameWidget::GameWidget(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);
    setFocusPolicy(Qt::StrongFocus);
}

void GameWidget::updateState(const GameState& state) {
    m_currentState = state;
    update();
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    // Painting Map
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            QRect rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

            switch (m_currentState.board[y][x]) {
                case TileType::Wall:
                    painter.fillRect(rect, Qt::black);
                    break;
                case TileType::Corridor:
                    painter.fillRect(rect, Qt::darkGray);
                    break;
                case TileType::Berserk:
                    painter.fillRect(rect, Qt::blue);
                    break;
                default:
                    painter.fillRect(rect, Qt::white);
                    break;
            }
        }
    }

    // Painting Players
    for (const auto& player : m_currentState.players) {
        painter.setBrush(Qt::green);
        painter.drawEllipse(player.pos.x * TILE_SIZE, player.pos.y * TILE_SIZE, TILE_SIZE,
                            TILE_SIZE);
    }

    // Painting Demons
    for (const auto& demon : m_currentState.demons) {
        if (demon.isFrightened) {
            painter.setBrush(Qt::cyan);
        } else {
            painter.setBrush(Qt::darkRed);
        }

        painter.drawEllipse(demon.pos.x * TILE_SIZE, demon.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

        painter.setPen(Qt::white);
        QString label = "";
        switch (demon.type) {
            case DemonType::Imp:
                label = "I";
                break;
            case DemonType::Pinky:
                label = "P";
                break;
            case DemonType::Cacodemon:
                label = "C";
                break;
            case DemonType::LostSoul:
                label = "L";
                break;
        }
        painter.drawText(demon.pos.x * TILE_SIZE, demon.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                         Qt::AlignCenter, label);
        painter.setPen(Qt::black);
    }
}
void GameWidget::keyPressEvent(QKeyEvent* event) {
    PlayerInput input = PlayerInput::None;
    switch (event->key()) {
        case Qt::Key_W:
            input = PlayerInput::MoveUp;
            break;
        case Qt::Key_S:
            input = PlayerInput::MoveDown;
            break;
        case Qt::Key_A:
            input = PlayerInput::MoveLeft;
            break;
        case Qt::Key_D:
            input = PlayerInput::MoveRight;
            break;
    }

    if (input != PlayerInput::None) {
        emit inputDetected(input);
    }
}

}  // namespace DoomMan
