#include "MainWindow.h"
#include "NewWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    NewWindow w;

    /*QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取设备屏幕大小
    QRect screenRect = desktopWidget->screenGeometry();

    qDebug() << "screen size:\n";
    qDebug() << screenRect;

    w.resize(screenRect.x(), screenRect.y());
    */
    w.show();
    //w.showMaximized();


    return a.exec();
}
