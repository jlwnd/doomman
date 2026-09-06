#pragma once

#include <QWidget>

#include "common/Types.h"

class QListWidget;

namespace DoomMan {
/// Ekran końca gry – pokazuje tablicę wyników i przycisk wyjścia,
/// wyświetlany po śmierci lokalnego gracza.
class GameOverWidget : public QWidget {
    Q_OBJECT
   public:
    /// Tworzy widżet ekranu końca gry.
    /// @param parent Widżet-rodzic Qt.
    explicit GameOverWidget(QWidget* parent = nullptr);

    /// Wypełnia tablicę wyników graczami posortowanymi malejąco po punktach.
    /// @param state Stan gry z ostatniej klatki.
    void showScores(const GameState& state);

   signals:
    // Emitowany gdy gracz kliknie przycisk wyjścia.
    void sigExit();

   private:
    QListWidget* m_scoreList;
};
}  // namespace DoomMan
