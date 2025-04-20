#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <QAudioOutput>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer_one_sec_(new prac::QTimer(this)) //таймер для отсчёта времени в сек
    , alarm_timer_(new prac::QTimer(this)) //таймер будильника
    , player_(new prac::QMediaPlayer(this))
    , audioOutput_(new QAudioOutput(this))  // Для Qt6

{
    alarm_time_.setHMS(0,0,0);
    ui->setupUi(this);
    //Подключим таймер обновления данных timer_one_sec_ и функцияю времени
    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::CurrentTimeDate);
    connect(ui->action_load_file, &QAction::triggered, this, &MainWindow::LoadFromResources);
    // Таймер проверки будильника
    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::AlarmCount);
    //счётчик обновления данных каждую секунду
    timer_one_sec_.start(1000);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CurrentTimeDate() {
    prac::QDateTime now = prac::QDateTime::currentDateTime(); //Получаем текущие дату и время
    QTime snow = now.time();
    timer_one_sec_.setInterval(1000 - snow.msec());
    timer_one_sec_.start();
    QString timeText = now.toString("hh:mm:ss"); //формат времени
    ui->lbl_now->setText(timeText); //устанавливаем текст в окно
}

void MainWindow::LoadFromResources () {
    file_name_ = prac::QFileDialog::getOpenFileName(this,
                                                           QString::fromUtf8("Открыть файл"),
                                                           QDir::currentPath(),
                                                           "*.wav;*.mp3");
    if (!file_name_.isEmpty()) {
    QString shortfilename = QFileInfo(file_name_).fileName();
    ui->lbl_melody->setText(shortfilename);
    }
}

void MainWindow::SetAlarmTime() {
    int hours = ui->sb_hour->value();
    int minutes = ui->sb_min->value();
    int seconds = ui->sb_sec->value();
    alarm_time_.setHMS(hours , minutes , seconds);
}


void MainWindow::on_pb_start_stop_clicked() {
    start_button_ = !start_button_;

    if (start_button_) {
        ui->pb_start_stop->setText("Стоп");
        SetAlarmTime();
        // UpdateTimeToAlarm();
        AlarmCount();

    } else {
        ui->pb_start_stop->setText("Старт");
        ui->lbl_timeout->setText("Установите будильник");
        alarm_time_ = QTime();
        alarm_active_ = false;

    }
    lbl_timeout_update();
    player_.stop();

}


void MainWindow::AlarmCount() {

    prac::QTime now = prac::QTime::currentTime();
    timer_one_sec_.setInterval(1000 - now.msec());
    timer_one_sec_.start();

    int durationSeconds = now.secsTo(alarm_time_);
    // Если время уже прошло, считаем для следующего дня
    if (durationSeconds < 0) {
        durationSeconds += (24 * 3600);  // Добавляем 24 часа
    }

    if(start_button_ & (alarm_active_ == false)) {
        QTime timeLeft(0, 0, 0);
        timeLeft = timeLeft.addSecs(durationSeconds);
        ui->lbl_timeout->setText(timeLeft.toString("hh:mm:ss"));
    }else{
        return;
    }
}

void MainWindow::PlaySignal () {
    player_.setSource(QUrl::fromLocalFile(file_name_)); // или QUrl("qrc:/звук.mp3") для ресурсов
    audioOutput_.setVolume(0.5);  // Громкость 0-1
    player_.setAudioOutput(&audioOutput_);  // Для Qt6

    player_.play();
    alarm_active_ = true;
}

void MainWindow::lbl_timeout_update () {
    if(!start_button_) {
        ui->lbl_timeout->setText("Установите будильник");
    }
}
