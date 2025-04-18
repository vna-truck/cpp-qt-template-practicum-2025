// Возьмите решение предыдущей задачи
// о фотоальбоме в качестве заготовки.
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <prac/QFileDialog>
#include <QPixmap>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cur_file_index_(-1)
    , timer(new prac::QTimer(this))

{
    ui->setupUi(this);
    loadFromResources();
    FitImage();
    SetupMenuActions();
    //Подключим таймер
    connect(timer, &prac::QTimer::timeout, this, &MainWindow::TimerTimeout);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete ui;
}

//Моё меню
void MainWindow::SetupMenuActions() {
    connect(ui->action_up_windows, &QAction::triggered, this, &MainWindow::toggleAlwaysOnTop);
    connect(ui->action_use_resources, &QAction::triggered, this, &MainWindow::loadFromResources);
    connect(ui->action_choose_dir, &QAction::triggered, this, &MainWindow::SelectDirectory);
    //таймеры
    connect(ui->action_0sec, &QAction::triggered, this, [this](){ SetTimerInterval(0); });
    connect(ui->action_1sec, &QAction::triggered, this, [this](){ SetTimerInterval(1000); });
    connect(ui->action_5sec, &QAction::triggered, this, [this](){ SetTimerInterval(5000); });
    connect(ui->action_10sec, &QAction::triggered, this, [this](){ SetTimerInterval(10000); });
}

//Контекстное меню(обязательно с маленькой буквы)
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(ui->action_up_windows);
    menu.addSeparator();
    menu.addAction(ui->action_use_resources);
    menu.addAction(ui->action_choose_dir);
    menu.addSeparator();

    QMenu* timerMenu = menu.addMenu("Период переключения");
    timerMenu->addAction(ui->action_0sec);
    timerMenu->addAction(ui->action_1sec);
    timerMenu->addAction(ui->action_5sec);
    timerMenu->addAction(ui->action_10sec);

    menu.addSeparator();
    menu.addAction(ui->close_programm);

    menu.exec(event->globalPos());
}

QString MainWindow::GetCurrentFile() {
    if (image_files_.isEmpty() || cur_file_index_ < 0 || cur_file_index_ >= image_files_.size()) {
        return QString();
    }
    return image_files_[cur_file_index_];

}

void MainWindow::ShowNextImage() {
    if (image_files_.isEmpty()) return;
    cur_file_index_ = (cur_file_index_ + 1) % image_files_.size();
    SetPixmap(GetCurrentFile());
}

void MainWindow::ShowPreviousImage() {
    if (image_files_.isEmpty()) return;
    cur_file_index_ = (cur_file_index_ - 1 + + image_files_.size()) % image_files_.size();
    SetPixmap(GetCurrentFile());
}

QPixmap ResizeImgToFit(const QPixmap &src, int window_width, int window_height) {
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) / window_width;
    double h_ratio = double(img_h) / window_height;

    if ( w_ratio > h_ratio ) {
        return src.scaledToHeight(window_height);
    } else {
        return src.scaledToWidth(window_width);
    }
}

void MainWindow::FitImage()
{
    Q_ASSERT(!active_pixmap.isNull());

    // 1. Вызовите ResizeImgToFit.
    // Получаем масштабированное изображение под размер окна
    QPixmap scaled_pixmap = ResizeImgToFit(active_pixmap, width(), height());

    // 2. Поместите изображение в lbl_new_.
    // Устанавливаем изображение в метку
    lbl_new_.setPixmap(scaled_pixmap);

    // 3. Измените размер lbl_new_.
    // Изменяем размер метки под размер изображения
    lbl_new_.resize(scaled_pixmap.size());

    // Вычисляем координаты для центрирования метки
    int x = (width() - lbl_new_.width()) / 2;
    int y = (height() - lbl_new_.height()) / 2;

    // 4. Переместите lbl_new_, пользуясь формулами из условия.
    // Перемещаем метку в вычисленную позицию
    lbl_new_.move(x, y);
}

void MainWindow::SetFolder(const QString &d)
{
    UpdateEnabled();
    current_folder_ = d;
    cur_file_index_ = 0;
    SetPixmap(GetCurrentFile());
}
//Загружает изображение из файла по указанному пути (path)
void MainWindow::SetPixmap(const QString path) {
    active_pixmap = QPixmap(path);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}

void MainWindow::UpdateEnabled() {
    // Количество изображений в папке.
    int max_images = QDir(current_folder_).entryList().size();

    // Устанавливаем активность кнопки «влево».
    ui->btn_left->setEnabled(cur_file_index_ > 0);

    // Устанавливаем активность кнопки «вправо».
    ui->btn_right->setEnabled(cur_file_index_ < max_images - 1);
}

void MainWindow::on_btn_left_clicked() {
    ShowPreviousImage();
    FitImage();
}


void MainWindow::on_btn_right_clicked() {
    ShowNextImage();
    FitImage();
}

//Функция поверх всех окон
void MainWindow::toggleAlwaysOnTop(bool checked) {
    setWindowFlag(Qt::WindowStaysOnTopHint, checked);
    show();
}

//Используем фото из ресурсов
void MainWindow::loadFromResources()
{
    image_files_.clear();
    current_folder_ = ":/cats/images";
    QDir resDir(current_folder_);
    QStringList files = resDir.entryList({"*.jpg","*.png"}, QDir::Files, QDir::Name);

    for (const QString& file : files) {
        QString fullPath = current_folder_ + "/" + file;
        QPixmap pixmap(fullPath);
        if (!pixmap.isNull()) {
            image_files_.append(fullPath);
        }
    }

    loadFirstImage();
}

void MainWindow::loadFirstImage()
{
    lbl_new_.clear();
    if (image_files_.isEmpty()) {
        UpdateButtonsState(false);
        return;
    }

    cur_file_index_ = 0;
    SetPixmap(image_files_[cur_file_index_]);
    FitImage();
    UpdateButtonsState(true);
}

//Делает кнопки активными
void MainWindow::UpdateButtonsState(bool enabled)
{
    ui->btn_left->setEnabled(enabled);
    ui->btn_right->setEnabled(enabled);
}

//Выбор изображения из папки
void MainWindow::SelectDirectory()
{
    QString dir = prac::QFileDialog::getExistingDirectory(this, "Выберите папку с изображениями");
    if (dir.isEmpty()) return;
    current_folder_ = dir;
    image_files_.clear();
    QDir directory(dir);
    QStringList files = directory.entryList({"*.jpg", "*.png", "*.jpeg", "*.bmp"}, QDir::Files, QDir::Name);

    for (const QString& file : files) {
        QString fullPath = directory.filePath(file);
        QPixmap pixmap(fullPath);
        if (!pixmap.isNull()) {
            image_files_.append(fullPath);
        }
    }

    loadFirstImage();
}

void MainWindow::TimerTimeout() {
    if (!image_files_.isEmpty()) {
        ShowNextImage();
        FitImage();
    }
}

void MainWindow::SetTimerInterval(int interval) {
    timer->stop();
    if (interval > 0) {

        timer->start(interval);
    }

    // Update menu checkmarks
    ui->action_0sec->setChecked(interval == 0);
    ui->action_1sec->setChecked(interval == 1000);
    ui->action_5sec->setChecked(interval == 5000);
    ui->action_10sec->setChecked(interval == 10000);
}
