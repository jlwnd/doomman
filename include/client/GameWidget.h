#pragma once
#include <QWidget>
#include "common/Types.h"

namespace Doom {
class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget* parent = nullptr);
public slots:
    void updateState(const GameState& state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    GameState m_currentState;
    const int TILE_SIZE = 30;
};
}