#pragma once

#include <QWidget>

#include "client/Leaderboard.h"

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

    /// Wypełnia tablicę wyników gotowym rankingiem graczy.
    /// @param board Ranking zbudowany po stronie modelu klienta.
    void showScores(const Leaderboard& board);

   signals:
    // Emitowany gdy gracz kliknie przycisk wyjścia.
    void sigExit();

   private:
    QListWidget* m_scoreList;
};
}  // namespace DoomMan
