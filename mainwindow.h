#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QPixmap>
#include <QTime>
#include <QPoint>
#include <QMouseEvent>

extern int okl;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPixmap m_pixmap;

    void sleep(unsigned int msec);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint dragPosition;

private slots:
    void ScreenCaptureSlot();

    void on_closeButton_clicked();

    void AnyPartSlot();

    void InformationFile();

    void read_emit(QPixmap send);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
