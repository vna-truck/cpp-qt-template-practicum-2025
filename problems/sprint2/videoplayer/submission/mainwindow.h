#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <prac/QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_choose_clicked();
    void on_position_changed(qint64 position);
    void on_media_status_changed(QMediaPlayer::MediaStatus status);
    void on_playback_state_changed(QMediaPlayer::PlaybackState newState);

    void on_btn_pause_clicked();

    void on_sld_volume_valueChanged(int value);

    void on_sld_pos_valueChanged(int value);
private:
    Ui::MainWindow *ui;
    prac::QMediaPlayer player_{this};
    QAudioOutput audio_output_{this};
    bool position_changing_ = false;
    QString file_adress_;
    bool play_is_on_;

};
#endif // MAINWINDOW_H
