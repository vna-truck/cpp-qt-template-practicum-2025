// Возьмите решение предыдущей задачи
// о фотоальбоме в качестве заготовки.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <prac/QTimer>

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

    //устанавливает путь к папке с файлами
    void SetFolder(const QString& d);

    void SetPixmap(const QString path);

    void FitImage();

    QString GetCurrentFile();

    void UpdateEnabled();
    void loadFromResources();

    void UpdateButtonsState(bool enabled);
    void ShowNextImage();
    void ShowPreviousImage();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
private slots:
    void on_btn_left_clicked();
    void SelectDirectory();
    void on_btn_right_clicked();

    void toggleAlwaysOnTop(bool checked);
    void SetTimerInterval(int interval);
    void TimerTimeout();
private:
    void resizeEvent(QResizeEvent *event) override;
    void loadFirstImage();
private:
    // Передаём this (форму) в конструктор элемента.
    QLabel lbl_new_{this};
    Ui::MainWindow *ui;
    QPixmap active_pixmap;
    QString current_folder_;
    int cur_file_index_ = 0;
    QStringList image_files_;
    void SetupMenuActions();
    prac::QTimer *timer;

};
#endif // MAINWINDOW_H
