#include "mainwindow.h"
#include <QApplication>
#include "sreenshoot.h"
#include <QDir>
#include <QString>
#include <QPixmap>
#include <QSplashScreen>
#include <QMovie>
#include <synchapi.h>

int okl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");

    QString fullPath = "E:\\ScreenCapture1\\save";
    QDir dir(fullPath);

    QPixmap pix("E:\\ScreenCapture1\\image\\loading1_2.jpg");
    pix.fill(Qt::transparent);
    QSplashScreen splash(pix);
    splash.setWindowOpacity(0.9);
    QLabel label(&splash);
    QMovie mv("E:\\ScreenCapture1\\image\\loading1_1.gif");
    label.setMovie(&mv);

    mv.start();
    splash.show();
    splash.setCursor(Qt::BlankCursor);

    for(int i=0; i<111111; i++)
    {
        if(!dir.exists())
        {
            dir.mkpath(fullPath);//创建多级目录
        }
        QCoreApplication::processEvents();
        if(i == 111110)
            splash.hide();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
