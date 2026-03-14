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
   signals:
    void inputDetected(PlayerInput input);

   protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

   private:
    GameState m_currentState;
    const int TILE_SIZE = 30;
};
}  // namespace Doom