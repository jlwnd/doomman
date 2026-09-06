#include "client/widgets/GameWidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QString>

namespace DoomMan {

/// Indeksy tekstur w GameWidget::m_tex.
enum Tex {
    TEX_WALL,
    TEX_FLOOR,
    TEX_VOID,
    TEX_GATE,
    TEX_AMMO,
    TEX_BERSERK,
    TEX_PLAYER,
    TEX_IMP,
    TEX_PINKY,
    TEX_CACO,
    TEX_LOSTSOUL
};

GameWidget::GameWidget(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(BOARD_SIZE * TILE_SIZE, BOARD_SIZE * TILE_SIZE);

    const char* names[] = {"wall",   "floor", "void",  "gate",      "ammo",    "berserk",
                           "player", "imp",   "pinky", "cacodemon", "lostsoul"};
    for (const char* name : names) {
        m_tex.emplace_back().load(QString("assets/textures/%1.png").arg(name));
    }
}

void GameWidget::drawTexture(QPainter& p, const QPixmap& tex, int px, int py) {
    p.drawPixmap(QRect(px * TILE_SIZE, py * TILE_SIZE, TILE_SIZE, TILE_SIZE), tex);
}

void GameWidget::updateState(const GameState& state) {
    m_currentState = state;
    update();
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            switch (m_currentState.board.at({x, y})) {
                case TileType::Wall:
                    drawTexture(painter, m_tex[TEX_WALL], x, y);
                    break;
                case TileType::Empty:
                    drawTexture(painter, m_tex[TEX_FLOOR], x, y);
                    break;
                case TileType::Corridor:
                    drawTexture(painter, m_tex[TEX_FLOOR], x, y);
                    drawTexture(painter, m_tex[TEX_AMMO], x, y);
                    break;
                case TileType::Berserk:
                    drawTexture(painter, m_tex[TEX_FLOOR], x, y);
                    drawTexture(painter, m_tex[TEX_BERSERK], x, y);
                    break;
                default:
                    drawTexture(painter, m_tex[TEX_FLOOR], x, y);
                    break;
            }
        }
    }

    for (const auto& player : m_currentState.players) {
        if (!player.isAlive) continue;
        drawTexture(painter, m_tex[TEX_PLAYER], player.pos.x, player.pos.y);
    }

    for (const auto& demon : m_currentState.demons) {
        if (!demon.isAlive) continue;

        int tex = TEX_IMP;
        switch (demon.type) {
            case DemonType::Imp:
                tex = TEX_IMP;
                break;
            case DemonType::Pinky:
                tex = TEX_PINKY;
                break;
            case DemonType::Cacodemon:
                tex = TEX_CACO;
                break;
            case DemonType::LostSoul:
                tex = TEX_LOSTSOUL;
                break;
        }
        drawTexture(painter, m_tex[tex], demon.pos.x, demon.pos.y);

        if (demon.isFrightened) {
            QRect r(demon.pos.x * TILE_SIZE, demon.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            painter.fillRect(r, QColor(40, 90, 220, 110));
        }
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
