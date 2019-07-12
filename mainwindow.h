#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QPoint>

class QTimer;
class QCloseEvent;
class QMediaPlayer;
class QMouseEvent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();
    void onOneMinute_timeout();
    void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    QSystemTrayIcon *m_tray;
    int cur_seconds_left;
    QMediaPlayer *player;
    const int pomodoro_secs = 25*60;
    //const int pomodoro_secs = 5;
    QPoint diffpoint;
};

#endif // MAINWINDOW_H
