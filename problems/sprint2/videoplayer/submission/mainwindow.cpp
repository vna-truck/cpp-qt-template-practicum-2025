#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <prac/QMediaPlayer>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    // Присоедините аудио и видеовыходы к плееру.
    // 1. Подключаем аудиовыход к плееру
    player_.setAudioOutput(&audio_output_);
    // 2. Подключаем видеовыход к плееру
    player_.setVideoOutput(ui->video_output);

    connect(&player_, &prac::QMediaPlayer::positionChanged, this, &MainWindow::on_position_changed);
    connect(&player_, &prac::QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_media_status_changed);
    connect(&player_, &prac::QMediaPlayer::playbackStateChanged, this, &MainWindow::on_playback_state_changed);
    connect(ui->sld_pos, &QSlider::valueChanged, this, &MainWindow::on_sld_pos_valueChanged);
    audio_output_.setVolume(1.f);
}

void MainWindow::on_position_changed(qint64 position) {
    // Реализуем перемещеине ползунка во время проигрывания файла.
    position_changing_ = true;
    ui->sld_pos->setValue(position);
    position_changing_ = false;

}

void MainWindow::on_media_status_changed(QMediaPlayer::MediaStatus) {
    // Устанавливаем максимальное значение продолжительности файла
    ui->sld_pos->setMaximum(player_.duration());
}

void MainWindow::on_playback_state_changed(QMediaPlayer::PlaybackState new_state) {
    if(player_.playbackState() == QMediaPlayer::PlaybackState::PlayingState) {
        ui->btn_pause->setText("⏵");
    }else{
        ui->btn_pause->setText("⏸");
    }
}

void MainWindow::on_btn_choose_clicked()
{
    // загрузка видео из папки
    file_adress_ = prac::QFileDialog::getOpenFileName(this,
                                                      QString::fromUtf8("Открыть файл"),
                                                      "C:/Users/alexs/Videos",
                                                      "*.mov;*.mkv");
    player_.setSource(QUrl::fromLocalFile(file_adress_));
    player_.setAudioOutput(&audio_output_);
    player_.setVideoOutput(ui->video_output);
    audio_output_.setVolume(0.5);  // Громкость 0-1
    player_.play();

}

void MainWindow::on_btn_pause_clicked()
{
    // кнопка паузы
    if(player_.playbackState() == QMediaPlayer::PlaybackState::PlayingState) {
        player_.pause();
    }else if(player_.playbackState() == QMediaPlayer::PlaybackState::StoppedState) {
        //тут надо установить указатель на 0
        player_.setPosition(0);
        player_.play();
    }else{
        player_.play();
    }
}

void MainWindow::on_sld_volume_valueChanged(int value)
{
    // громкость.
    if (player_.audioOutput()) {  // Проверяем, подключен ли аудиовыход
        float volume = qBound(0.0f, value / 100.0f, 1.0f);  // Ограничение 0-1
        player_.audioOutput()->setVolume(volume);
    }
}

void MainWindow::on_sld_pos_valueChanged(int value)
{
    //перемещение ползунка и перемонтка файла
    if(!position_changing_){
    player_.setPosition(value);

   }
}

MainWindow::~MainWindow()
{
    delete ui;
}
