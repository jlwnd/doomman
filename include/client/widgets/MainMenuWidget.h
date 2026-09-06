#pragma once
#include <QString>
#include <QWidget>

class QLineEdit;

namespace DoomMan {
/// Ekran startowy – pozwala podać pseudonim i wybrać tryb rozgrywki.
class MainMenuWidget : public QWidget {
    Q_OBJECT
   public:
    /// Tworzy widżet menu głównego.
    /// @param parent Widżet-rodzic Qt.
    explicit MainMenuWidget(QWidget* parent = nullptr);

   signals:
    /// Emitowany po wybraniu hostowania gry.
    /// @param nick Pseudonim gracza-hosta.
    void sigHostGame(const QString& nick);

    /// Emitowany po wybraniu dołączenia do gry.
    /// @param nick Pseudonim dołączającego gracza.
    /// @param host Adres IP hosta, do którego dołączamy.
    void sigJoinGame(const QString& nick, const QString& host);

    /// Emitowany po wybraniu wyjścia z programu.
    void sigExit();

   private slots:
    void onHostClicked();
    void onJoinClicked();
    void onExitClicked();

   private:
    QLineEdit* m_nickEdit;
    QLineEdit* m_hostEdit;
};
}  // namespace DoomMan
