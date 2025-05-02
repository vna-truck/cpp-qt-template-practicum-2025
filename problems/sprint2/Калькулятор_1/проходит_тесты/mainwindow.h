#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDigitClicked();
    void onOperationClicked();  // Только одно объявление
    void onEqualsClicked(); 
    void onClearClicked();
    void onSignClicked();
    void onDecimalClicked();
    void onBackspaceClicked();
    void onMemorySaveClicked();
    void onMemoryReadClicked();
    void onMemoryClearClicked();

private:
    Ui::MainWindow *ui;
    Calculator calculator_;
    Operation current_operation_ = NO_OPERATION;
    QString input_number_;
    double active_number_ = 0.0;
    double memory_cell_ = 0.0;
    bool memory_saved_ = false;
    bool memory_used_ = false;
    bool result_shown_ = false;
    QString getOperationSymbol(Operation op); 
    void updateResult();
    void resetCalculator();
    void performOperation();
};

#endif // MAINWINDOW_H