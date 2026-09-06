#pragma once

#include <QWidget>

#include "common/Types.h"

class QListWidget;
class QPushButton;

namespace DoomMan {
class LobbyWidget : public QWidget {
    Q_OBJECT
   public:
    /// Tworzy widżet poczekalni.
    /// @param parent Widżet-rodzic Qt.
    explicit LobbyWidget(QWidget* parent = nullptr);

    /// Włącza przycisk startu tylko dla hosta rozgrywki.
    /// @param isHost Czy lokalny gracz jest hostem.
    void setHost(bool isHost);

   public slots:
    /// Aktualizuje wyświetlany stan poczekalni i odświeża widok.
    /// @param state Nowy stan poczekalni odebrany z serwera.
    void updateLobby(const GameState& state);

   signals:
    // Emitowany gdy gracz kliknie przycisk gotowości.
    void sigGameReady();

    // Emitowany gdy host kliknie przycisk startu rozgrywki.
    void sigGameStart();

   private:
    QListWidget* m_playerList;
    QPushButton* m_startButton;
};
}  // namespace DoomMan
