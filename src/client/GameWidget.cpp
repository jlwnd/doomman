#include "client/GameWidget.h"
#include <QPainter>
#include <QPaintEvent>

namespace Doom {

GameWidget::GameWidget(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void GameWidget::updateState(const GameState& state) {
    m_currentState = state;
    update();
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            QRect rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            
            switch (m_currentState.board[y][x]) {
                case TileType::Wall:
                    painter.fillRect(rect, Qt::black); break;
                case TileType::Corridor:
                    painter.fillRect(rect, Qt::darkGray); break;
                case TileType::Berserk:
                    painter.fillRect(rect, Qt::blue); break;
                case TileType::SpawnPoint:
                    painter.fillRect(rect, Qt::red); break;
                default:
                    painter.fillRect(rect, Qt::white); break;
            }
        }
    }

    for (const auto& player : m_currentState.players) {
        painter.setBrush(Qt::green);
        painter.drawEllipse(player.pos.x * TILE_SIZE, player.pos.y * TILE_SIZE, 
                            TILE_SIZE, TILE_SIZE);
    }
}

} // namespace Doom