#include <QApplication>
#include <QFile>
#include <QFont>
#include <QFontDatabase>

#include "client/MainWindow.h"
#include "client/Theme.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QString family = QStringLiteral("monospace");
    QFile fontFile(QStringLiteral("assets/fonts/PressStart2P-Regular.ttf"));
    if (fontFile.open(QIODevice::ReadOnly)) {
        const int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        family = QFontDatabase::applicationFontFamilies(fontId).value(0, family);
    }
    a.setFont(QFont(family));
    a.setStyleSheet(DoomMan::appStyleSheet(family));

    DoomMan::MainWindow window;
    window.show();

    return a.exec();
}
