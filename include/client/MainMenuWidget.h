#pragma once
#include <QWidget>
#include <QString>

class QLineEdit;

namespace Doom {
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
}  // namespace Doom
