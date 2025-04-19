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

    QDateTime GetAlarmMoment() const {
        return alarm_moment_;
    }

private slots:
    // Тут объявите слоты.

    void OnTimer();
    void on_pb_start_stop_clicked();
    void ProcessAlarm();
    void GetAlarmTime();
    void LoadFromResources();
    // void PlaySignal();
private:
    Ui::MainWindow *ui;
    QDateTime alarm_moment_;
    prac::QTimer timer_one_sec_{this};

    bool start_button_state_ = false;
    bool alarm_playing_ = false;
    QString file_adress_;
    QAudioOutput audioOutput_;  // Для Qt6
    prac::QMediaPlayer player_{this};
};
