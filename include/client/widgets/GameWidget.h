#pragma once
#include <QPixmap>
#include <QWidget>
#include <vector>

#include "common/Types.h"

class QPainter;

namespace DoomMan {
/// Widżet renderujący planszę gry i przechwytujący sterowanie klawiaturą.
class GameWidget : public QWidget {
    Q_OBJECT
   public:
    /// Tworzy widżet gry.
    /// @param parent Widżet-rodzic Qt.
    explicit GameWidget(QWidget* parent = nullptr);
   public slots:
    /// Aktualizuje wyświetlany stan gry i odświeża widok.
    /// @param state Nowy stan gry odebrany z serwera.
    void updateState(const GameState& state);
   signals:
    /// Emitowany po wykryciu wciśnięcia klawisza kierunku.
    /// @param input Wykryty kierunek ruchu.
    void inputDetected(PlayerInput input);

   protected:
    /// Rysuje planszę i obiekty gry.
    /// @param event Zdarzenie rysowania Qt.
    void paintEvent(QPaintEvent* event) override;

    /// Przechwytuje klawisze sterowania (WASD) i emituje inputDetected.
    /// @param event Zdarzenie klawiatury Qt.
    void keyPressEvent(QKeyEvent* event) override;

   private:
    /// Rysuje pojedynczą teksturę w kafelku (px, py) na siatce planszy.
    /// @param p Painter Qt.
    /// @param tex Tekstura 16x16 do narysowania.
    /// @param px Kolumna kafelka.
    /// @param py Wiersz kafelka.
    void drawTexture(QPainter& p, const QPixmap& tex, int px, int py);

    GameState m_currentState;
    const int TILE_SIZE = 32;

    std::vector<QPixmap> m_tex;
};
}  // namespace DoomMan
