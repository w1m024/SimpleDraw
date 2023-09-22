#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    w.showMaximized(); //主程序窗口最大化输出

    return a.exec();
}
