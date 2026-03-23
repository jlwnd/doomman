#include <QApplication>
#include "client/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    Doom::MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}