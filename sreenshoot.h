#ifndef SREENSHOOT_H
#define SREENSHOOT_H

#include <QMouseEvent>
#include <QKeyEvent>
#include <QRubberBand>
#include <QLabel>
#include <QImage>
#include <QPalette>
#include <QPixmap>
#include <QScreen>
#include "mainwindow.h"

class ScreenShoot : public QMainWindow
{
    Q_OBJECT

public:

    static ScreenShoot* Instance()
    {
       if(!instance)
           instance = new ScreenShoot();
       return instance;
    }


    void mouseMoveEvent(QMouseEvent *e);      // 处理鼠标移动
    void mousePressEvent(QMouseEvent *e);     // 处理鼠标按下
    void mouseReleaseEvent(QMouseEvent *e);   // 处理鼠标释放
    void setbackground(int width,int height); // 初始化程序背景
    void grabScreen();                        // 根据选取截屏，保存并打开图片
    void setLabel();                          // 动态显示截图区域尺寸
    void keyPressEvent(QKeyEvent *e);         // 处理esc取消按键
     ~ScreenShoot();
    void show();                              // 重写 show() 每次显示都重新渲染窗体背景 单例需要
    void send_emit();

signals:
    void start_emit(QPixmap);

public:
    QRubberBand* g_rubber;
    QPoint origin;                            // 记录鼠标按下坐标
    QPoint end;                               // 记录鼠标释放坐标
    QLabel* label;                            // 显示截图区域尺寸
    QImage* bg;                               // 记录全屏图片
    int g_width;                              // 屏幕宽度
    int g_height;                             // 屏幕高度
    static ScreenShoot* instance;
    ScreenShoot();
};

#endif // SREENSHOOT_H
