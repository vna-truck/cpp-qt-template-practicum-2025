#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>
#include <prac/QDateTime>

QString TimeToString(QTime time) {
    return QString("%1:%2:%3").arg(time.hour(), 2, 10, QChar('0')).arg(time.minute(), 2, 10, QChar('0')).arg(time.second(), 2, 10, QChar('0'));
}

QString TimeToString(std::chrono::milliseconds ms) {
    return TimeToString(QTime::fromMSecsSinceStartOfDay(ms.count() + 500));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer_one_sec_(new prac::QTimer(this)) //таймер для отсчёта времени в сек

{
    ui->setupUi(this);
    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::OnTimer);
    timer_one_sec_.start(1000);
}

void MainWindow::OnTimer() {
    QDateTime now = prac::QDateTime::currentDateTime(); //Получаем текущие дату и время
    QTime snow = now.time();//текущее время из датывремя
    timer_one_sec_.setInterval(1000 - snow.msec()); //Сколько осталось до конца текущей секунды
    timer_one_sec_.start(); //запускаем
    QString timeText = snow.toString("hh:mm:ss"); //формат времени
    ui->lbl_now->setText(timeText); //устанавливаем текст в окно
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_start_stop_clicked() {
    start_button_state_ = !start_button_state_;
    //проверить состояние кнопки
    if(start_button_state_) {
        //высчитать время срабатывания QDateTime alarm_moment_ с помощью
        GetAlarmTime();
        ui->pb_start_stop->setText("Стоп");
            //строчки для теста. Потом заменить на метод высчитывания времени до будильника
            QString testtime = alarm_moment_.toString();
            ui->lbl_timeout->setText(testtime);
    }else{
        ui->pb_start_stop->setText("Старт");
            //ниже строчки для теста
            QString testtime = alarm_moment_.toString();
            ui->lbl_timeout->setText("Установите будильник");
    }

}

void MainWindow::GetAlarmTime() {
    auto now = prac::QDateTime::currentDateTime();
    QTime alarm_time = QTime(ui->sb_hour->value(), ui->sb_min->value(), ui->sb_sec->value());
    alarm_moment_ = QDateTime(now.date(), alarm_time);
    qDebug() <<  alarm_moment_;
}
