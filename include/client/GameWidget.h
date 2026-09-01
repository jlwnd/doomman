#pragma once
#include <QWidget>

#include "common/Types.h"

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
    GameState m_currentState;
    const int TILE_SIZE = 30;
};
}  // namespace DoomMan
