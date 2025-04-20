#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>
#include <prac/QDateTime>
#include <prac/QMediaPlayer>
#include <QAudioOutput>

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
    , player_(new prac::QMediaPlayer(this))  // Для Qt6
    , audioOutput_(new QAudioOutput(this))


{
    ui->setupUi(this);

    connect(ui->action_load_file, &QAction::triggered, this, &MainWindow::LoadFromResources);
    // Таймер часов
    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::OnTimer);
    // Таймер проверки будильника
    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::ProcessAlarm);
    // timer_one_sec_.start(1000);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::LoadFromResources () {
    file_adress_ = prac::QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Открыть файл"),
                                                    "C:/Users/alexs/Music",
                                                    "*.wav;*.mp3");
    if (!file_adress_.isEmpty()) {
        QString shortfilename = QFileInfo(file_adress_).fileName();
        ui->lbl_melody->setText(shortfilename);
    }
    player_.setSource(file_adress_); // или QUrl("qrc:/звук.mp3") для ресурсов
    audioOutput_.setVolume(0.5);  // Громкость 0-1
    player_.setAudioOutput(&audioOutput_);  // Для Qt6
}

void MainWindow::OnTimer() {
    auto now = prac::QDateTime::currentDateTime(); //Получаем текущие дату и время
    QTime snow = now.time();//текущее время из датывремя
    timer_one_sec_.setInterval(1000 - snow.msec()); //Сколько осталось до конца текущей секунды
    timer_one_sec_.start(); //запускаем
    QString timeText = snow.toString("hh:mm:ss"); //формат времени
    ui->lbl_now->setText(timeText); //устанавливаем текст в окно
}

// void MainWindow::OnTimer() {
//     auto now = prac::QTime::currentTime();
//     ui->lbl_now->setText(now.toString("hh:mm:ss"));

//     int delay = 1000 - now.msec();
//     if (delay < 0) delay = 0;
//     timer_one_sec_.start(delay);

//     ProcessAlarm();
// }

void MainWindow::on_pb_start_stop_clicked() { //нажатие на кнопку старт-стоп
    start_button_state_ = !start_button_state_;
    //проверить состояние кнопки
    if(start_button_state_) {
        //высчитать время срабатывания QDateTime alarm_moment_ с помощью
        GetAlarmTime();
        ui->pb_start_stop->setText("Стоп");
        ProcessAlarm();
    }else{
        ui->pb_start_stop->setText("Старт");
        alarm_playing_ = false;
        player_.stop();
        alarm_moment_ = prac::QDateTime{};
        ProcessAlarm();


    }

}

//Старый вариант
// void MainWindow::GetAlarmTime() { // время срабатывания будильника
//     auto now = prac::QDateTime::currentDateTime();
//     QTime alarm_time = QTime(ui->sb_hour->value(), ui->sb_min->value(), ui->sb_sec->value());
//     alarm_moment_ = QDateTime(now.date(), alarm_time);
//     int durationSeconds = now.secsTo(alarm_moment_);
//     // Если время уже прошло, считаем для следующего дня
//     if (durationSeconds < 0) {
//         alarm_moment_ = alarm_moment_.addDays(1);  // Добавляем 24 часа，если время будильника прошло.
//     }

// }

void MainWindow::GetAlarmTime() { // время срабатывания будильника
    auto now = prac::QDateTime::currentDateTime();
    auto alarm_time = prac::QTime(ui->sb_hour->value(), ui->sb_min->value(), ui->sb_sec->value());
    alarm_moment_ = prac::QDateTime(now.date(), alarm_time);
    // Если время уже прошло, считаем для следующего дня
    if (alarm_moment_ <= now) {
        alarm_moment_ = alarm_moment_.addDays(1);  // Добавляем 24 часа，если время будильника прошло.
    }

}


// void MainWindow::ProcessAlarm() { //изменение состояния lbl_timout
//     auto now = prac::QDateTime::currentDateTime();
//     qint64 secs_left;
//     secs_left = now.secsTo(alarm_moment_);
//     QTime time_left(0, 0, 0);
//     time_left = time_left.addSecs(secs_left);
//     if(start_button_state_ & !alarm_playing_) {
//         QString texttime = time_left.toString("hh:mm:ss");
//         ui->lbl_timeout->setText(texttime);
//     //}else if(!start_button_state_ & !alarm_playing_) {
//     }else if(alarm_moment_ == prac::QDateTime()) {
//         ui->lbl_timeout->setText("Установите будильник");
//     }else{
//         return;
//     }
//     // if(secs_left < 0) {
//     if(now >= alarm_moment_) {
//         alarm_playing_ = true;
//         if (player_.playbackState() != QMediaPlayer::PlaybackState::PlayingState) {
//             player_.play();
//             ui->lbl_timeout->setText("Пора вставать");
//         }

//     }
// }

void MainWindow::ProcessAlarm() {
    if (alarm_moment_ == prac::QDateTime()) {
        ui->lbl_timeout->setText("Установите будильник");
        return;
    }

    auto now = prac::QDateTime::currentDateTime();
    if (now >= alarm_moment_) {
        ui->lbl_timeout->setText("Пора вставать");
        if (player_.playbackState() != QMediaPlayer::PlayingState) {
            player_.play();
        }
    } else {
        qint64 msecs_left = now.msecsTo(alarm_moment_);
        msecs_left += 1000;

        int hours = msecs_left / (1000 * 60 * 60);
        int minutes = (msecs_left % (1000 * 60 * 60)) / (1000 * 60);
        int seconds = (msecs_left % (1000 * 60)) / 1000;

        QString time_str = QString("%1:%2:%3")
                               .arg(hours, 2, 10, QChar('0'))
                               .arg(minutes, 2, 10, QChar('0'))
                               .arg(seconds, 2, 10, QChar('0'));

        ui->lbl_timeout->setText(time_str);
    }
}

