#include <QApplication>

#include "client/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    DoomMan::MainWindow window;
    window.show();

    return a.exec();
}
