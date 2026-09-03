#include <QApplication>
#include <QFontDatabase>

#include "client/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont("assets/fonts/PressStart2P-Regular.ttf");

    DoomMan::MainWindow window;
    window.show();

    return a.exec();
}
