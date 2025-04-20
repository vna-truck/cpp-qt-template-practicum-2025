#pragma once

#include <QMainWindow>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <prac/QDateTime>
#include <QAudioOutput>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void CurrentTimeDate();
    void LoadFromResources();
    void SetAlarmTime();
    void AlarmCount();
    void PlaySignal();
    void lbl_timeout_update();
private slots:

    void on_pb_start_stop_clicked();

private:
    Ui::MainWindow *ui;
    prac::QTimer timer_one_sec_{this};
    QTime alarm_time_;
    bool start_button_ = false;
    bool alarm_active_ = false;
    bool alarm_was_set_ = false;
    prac::QTimer alarm_timer_{this};
    prac::QMediaPlayer player_{this};
    QString file_name_;
    QAudioOutput audioOutput_;  // Для Qt6

};
