#pragma once
#include <QString>
#include <QWidget>

class QLineEdit;

namespace DoomMan {
class MainMenuWidget : public QWidget {
    Q_OBJECT
   public:
    explicit MainMenuWidget(QWidget* parent = nullptr);

   signals:
    void sigHostGame(const QString& nick);
    void sigJoinGame(const QString& nick);
    void sigExit();

   private slots:
    void onHostClicked();
    void onJoinClicked();
    void onExitClicked();

   private:
    QLineEdit* m_nickEdit;
};
} // namespace DoomMan
