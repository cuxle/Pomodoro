#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QEvent>
#include <QCloseEvent>
#include <QPainter>
#include <QMediaPlayer>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setHidden(true);


    player = new QMediaPlayer;
    //player->setMedia(QUrl("file:///D:/current_project/pomodoro/Pomodoro/res/audio/music.mp3"));
    player->setMedia(QUrl::fromLocalFile("D:/Program Files (x86)/BusInsight/music.mp3"));
    player->setVolume(50);

    m_timer = new QTimer;

    m_timer->setInterval(1000);

    QIcon icon(QPixmap("://res/images/pp.ico"));
    m_tray = new QSystemTrayIcon(icon, this);
    m_tray->setToolTip(tr("Pomodoro"));
    m_tray->show();
    connect(m_tray, &QSystemTrayIcon::activated, this, &MainWindow::onSystemTrayIconClicked);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onOneMinute_timeout);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onOneMinute_timeout()
{
    cur_seconds_left--;

    ui->label->setText(QString::number(cur_seconds_left));
    if(cur_seconds_left == 0) {
        QMessageBox::information(this, "TimeForABreak", "Hey, baby, It's time for a break!");
        ui->pushButton->setEnabled(true);
        m_timer->stop();
        player->play();
    }

}
void MainWindow::on_pushButton_clicked()
{
    cur_seconds_left = pomodoro_secs;
    ui->pushButton->setDisabled(true);
    m_timer->start();
}

void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if ( reason == QSystemTrayIcon::DoubleClick ) {
        if ( isVisible() ) {
            this->hide();
        } else {
            this->setWindowState(Qt::WindowActive);
            this->showNormal();
        }
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::WindowStateChange:
        if (isMinimized() == true) {
            m_tray->show();
            this->hide();
            return;
        }
        break;
    default:
        break;
    }

    return QMainWindow::changeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::Yes == QMessageBox::question(this, "Quit||Minimize", "Quit or Minimized")) {
        event->accept();
    } else {
        m_tray->show();
        this->hide();
        event->ignore();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);

    //p.drawPixmap(0,0,width(), height(), QPixmap("://res/images/pomodoro.jpg"));
    p.drawPixmap(rect(), QPixmap("://res/images/pp.png"));
    p.end();
}

//鼠标左键单击界面，拖动整个窗口移动，鼠标右击界面，界面退出
//鼠标左键单击界面，触发mountPressEvent(), 在这里边求出

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    static int64_t i = 0;
    //qDebug() << event->x() << event->y() << i++;
    if ( event->button() == Qt::RightButton ) {
        this->close();
    } else if( event->button() == Qt::LeftButton ) {
        //算出点击的位置举例原点的距离
        diffpoint = event->globalPos() - this->pos();
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //move(QPoint);
    static int j = 0;
    if ( event->buttons() == Qt::LeftButton ) {
        move(event->globalPos() - diffpoint);
        //qDebug() << event->x() << event->y() << j++;
    }
}
