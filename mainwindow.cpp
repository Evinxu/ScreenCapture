#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include "sreenshoot.h"
#include <QClipboard>
#include <QMimeData>

static QString savepath = "E:\\ScreenCapture1\\save\\";

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    //设置窗体为圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);

    setAutoFillBackground(true);
    setPalette(QPalette(QColor(144,238,144)));
    setWindowOpacity(0.85);          //窗体半透明

    ui->AnyPartButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->ScreenCaptureButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->closeButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");

    MainWindow::setMaximumSize(404,310);
    MainWindow::setMinimumSize(404,310);

    QObject::connect(ui->ScreenCaptureButton,SIGNAL(clicked(bool)),this,SLOT(ScreenCaptureSlot()));
    QObject::connect(ui->AnyPartButton,SIGNAL(clicked(bool)),this,SLOT(AnyPartSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) //点击左边鼠标
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
        event->accept();   //鼠标事件被系统接收
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        move(event->globalPos() - dragPosition);//移动窗口
        event->accept();
    }
}

//截全屏
void MainWindow::ScreenCaptureSlot()
{
    QString fullPath = "E:\\ScreenCapture1\\save";
    QDir dir(fullPath);
    if(!dir.exists())
    {
        dir.mkpath(fullPath);//创建多级目录
    }

    ui->pixMapLabel->clear();
    this->hide();
    QString fileName;
    fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss") + ".png";
    sleep(500);

    m_pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

    if(!m_pixmap.save(savepath+fileName,"png"))
    {
        qDebug()<<"Error!";
        this->show();
    }else
    {
        qDebug()<<"save ok!";
        this->show();
        //m_pixmap.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio);
        ui->pixMapLabel->setScaledContents(true);
        ui->pixMapLabel->setPixmap(m_pixmap);
        ui->pixMapLabel->setVisible(true);
    }

    //自动保存到剪切板
    if(!ui->pixMapLabel->pixmap()->isNull())
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setImage(ui->pixMapLabel->pixmap()->toImage());

        qDebug()<<"Label area have picture";
    }
    else
    {
        ui->pixMapLabel->setText("开始截图吧！！！");
        qDebug()<<"Label area not have picture";
    }
}

//延时
void MainWindow::sleep(unsigned int msec)
{
    QTime yanshihou = QTime::currentTime().addMSecs(msec);          //毫秒

    while(QTime::currentTime() < yanshihou)
    {
        QApplication::processEvents(QEventLoop::AllEvents,100);     //事件循环
    }
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

//选区截屏
void MainWindow::AnyPartSlot()
{
    QString fullPath = "E:\\ScreenCapture1\\save";
    QDir dir(fullPath);
    if(!dir.exists())
    {
        dir.mkpath(fullPath);//创建多级目录
    }

    ui->pixMapLabel->clear();
    this->showMinimized();
    ScreenShoot* instance = ScreenShoot::Instance();
    instance->show();

    sleep(2000);

    if(okl == 1)
    {
        sleep(4000);
        ScreenShoot screenshoot;
        QObject::connect(&screenshoot,SIGNAL(start_emit(QPixmap)),this,SLOT(read_emit(QPixmap)));
        screenshoot.send_emit();

        //自动保存到剪切板
        if(!ui->pixMapLabel->pixmap()->isNull())
        {
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setImage(ui->pixMapLabel->pixmap()->toImage());

            qDebug()<<"Label area have picture";
        }
        else
        {
            ui->pixMapLabel->setText("开始截图吧！！！");
            qDebug()<<"Label area not have picture";
        }

        qDebug()<<"okled is 1";
    }

    InformationFile();
}

void MainWindow::read_emit(QPixmap send)
{
    ui->pixMapLabel->setScaledContents(true);
    ui->pixMapLabel->setPixmap(send);
}

void MainWindow::InformationFile()          //获取文件信息
{
    QDir dir = savepath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    qDebug()<< "Bytes Filename created";
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        qDebug() << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
                               .arg(fileInfo.fileName())
                               .arg(fileInfo.created().toString("yyyy-MM-dd hh:dd:ss")));
    }
}

