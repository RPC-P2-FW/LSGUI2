#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    //window.resize(1200,750);
    window.setWindowTitle("Link System Controller");
    return app.exec();
}
