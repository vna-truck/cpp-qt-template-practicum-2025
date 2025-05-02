#pragma once

#include <QMainWindow>
#include "calculator.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void OnDigitClicked();
    void UpdateResult();
    void OnOperationClicked();
    void PerformOperation();
    void on_tb_reset_clicked();
    void on_tb_equal_clicked();
    void on_tb_negate_clicked();
    void on_tb_backspace_clicked();
    void on_tb_ms_clicked();
    void on_tb_mr_clicked();
    void on_tb_mc_clicked();
    void on_tb_comma_clicked();

private:
    Ui::MainWindow* ui;
    Calculator calculator_;
    Operation current_operation_ = NO_OPERATION;
    QString input_number_;
    double active_number_ = 0.0;
    double memory_cell_ = 0.0;
    bool memory_saved_ = false;
    bool memory_used_ = false;
    void ResetCalculator();
};
