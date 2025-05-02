#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключение цифровых кнопок
    for (int i = 0; i < 10; ++i) {
        QString buttonName = QString("pushButton_%1").arg(i < 9 ? i+1 : 11);
        if (QPushButton *button = findChild<QPushButton*>(buttonName)) {
            connect(button, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
        }
    }

    // Подключение кнопок операций
    connect(findChild<QPushButton*>("pushButton_18"), &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(findChild<QPushButton*>("pushButton_19"), &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(findChild<QPushButton*>("pushButton_20"), &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(findChild<QPushButton*>("pushButton_21"), &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(findChild<QPushButton*>("pushButton_23"), &QPushButton::clicked, this, &MainWindow::onOperationClicked);

    // Подключение других кнопок
    connect(findChild<QPushButton*>("pushButton_22"), &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(findChild<QPushButton*>("pushButton_14"), &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(findChild<QPushButton*>("pushButton_13"), &QPushButton::clicked, this, &MainWindow::onSignClicked);
    connect(findChild<QPushButton*>("pushButton_10"), &QPushButton::clicked, this, &MainWindow::onDecimalClicked);
    connect(findChild<QPushButton*>("pushButton_12"), &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);
    connect(findChild<QPushButton*>("pushButton_17"), &QPushButton::clicked, this, &MainWindow::onMemorySaveClicked);
    connect(findChild<QPushButton*>("pushButton_16"), &QPushButton::clicked, this, &MainWindow::onMemoryReadClicked);
    connect(findChild<QPushButton*>("pushButton_15"), &QPushButton::clicked, this, &MainWindow::onMemoryClearClicked);

    resetCalculator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDigitClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString digit = button->text();
    
    if (input_number_ == "0" && digit != "0") {
        input_number_.clear();
    }
    
    input_number_ += digit;
    active_number_ = input_number_.toDouble();
    updateResult();
}

void MainWindow::onOperationClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();
    
    if (current_operation_ != NO_OPERATION && input_number_.isEmpty()) {
        if (op == "+") current_operation_ = ADDITION;
        else if (op == "−") current_operation_ = SUBTRACTION;
        else if (op == "×") current_operation_ = MULTIPLICATION;
        else if (op == "÷") current_operation_ = DIVISION;
        else if (op == "xʸ") current_operation_ = POWER;
        
        ui->l_formula->setText(QString("%1 %2").arg(calculator_.Get()).arg(op == "xʸ" ? "^" : op));
        return;
    }
    
    if (!input_number_.isEmpty()) {
        calculator_.Set(input_number_.toDouble());
        input_number_.clear();
    }
    
    if (op == "+") current_operation_ = ADDITION;
    else if (op == "−") current_operation_ = SUBTRACTION;
    else if (op == "×") current_operation_ = MULTIPLICATION;
    else if (op == "÷") current_operation_ = DIVISION;
    else if (op == "xʸ") current_operation_ = POWER;
    
    ui->l_formula->setText(QString("%1 %2").arg(calculator_.Get()).arg(op == "xʸ" ? "^" : op));
}

void MainWindow::onEqualsClicked()
{
    if (current_operation_ == NO_OPERATION) return;
    
    performOperation();
    current_operation_ = NO_OPERATION;
}

void MainWindow::onClearClicked()
{
    calculator_.Clear();
    current_operation_ = NO_OPERATION;
    input_number_.clear();
    active_number_ = 0.0;
    ui->l_formula->clear();
    ui->l_result->setText("0");
}

void MainWindow::onSignClicked()
{
    if (input_number_.isEmpty()) {
        active_number_ *= -1;
        input_number_ = QString::number(active_number_);
    } else {
        if (input_number_.startsWith('-')) {
            input_number_.remove(0, 1);
        } else {
            input_number_.prepend('-');
        }
        active_number_ = input_number_.toDouble();
    }
    
    updateResult();
}

void MainWindow::onDecimalClicked()
{
    if (input_number_.contains('.')) return;
    
    if (input_number_.isEmpty()) {
        input_number_ = "0";
    }
    
    input_number_ += ".";
    updateResult();
}

void MainWindow::onBackspaceClicked()
{
    if (input_number_.isEmpty()) return;
    
    input_number_.chop(1);
    if (input_number_.isEmpty() || input_number_ == "-") {
        input_number_ = "0";
    }
    active_number_ = input_number_.toDouble();
    updateResult();
}

void MainWindow::onMemorySaveClicked()
{
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::onMemoryReadClicked()
{
    if (!memory_saved_) return;
    
    active_number_ = memory_cell_;
    input_number_ = QString::number(active_number_);
    updateResult();
}

void MainWindow::onMemoryClearClicked()
{
    memory_saved_ = false;
    memory_cell_ = 0.0;
    ui->l_memory->clear();
}

void MainWindow::updateResult()
{
    ui->l_result->setText(input_number_.isEmpty() ? QString::number(active_number_) : input_number_);
}

void MainWindow::resetCalculator()
{
    calculator_.Clear();
    current_operation_ = NO_OPERATION;
    input_number_.clear();
    active_number_ = 0.0;
    ui->l_formula->clear();
    ui->l_result->setText("0");
    ui->l_memory->clear();
}

void MainWindow::performOperation() {
    double secondOperand = input_number_.isEmpty() ? active_number_ : input_number_.toDouble();
    
    QString opSymbol;
    switch (current_operation_) {
        case ADDITION: opSymbol = "+"; break;
        case SUBTRACTION: opSymbol = "−"; break;
        case MULTIPLICATION: opSymbol = "×"; break;
        case DIVISION: opSymbol = "÷"; break;
        case POWER: opSymbol = "^"; break;
        default: return;
    }

    QString firstOperand = QString::number(calculator_.Get(), 'g', 12);
    QString secondOperandStr = QString::number(secondOperand, 'g', 12);
    ui->l_formula->setText(QString("%1 %2 %3 =").arg(firstOperand).arg(opSymbol).arg(secondOperandStr));

    switch (current_operation_) {
        case ADDITION: calculator_.Add(secondOperand); break;
        case SUBTRACTION: calculator_.Subtract(secondOperand); break;
        case MULTIPLICATION: calculator_.Multiply(secondOperand); break;
        case DIVISION: 
            if (secondOperand == 0) {
                ui->l_result->setText("Error");
                return;
            }
            calculator_.Divide(secondOperand);
            break;
        case POWER: calculator_.Set(std::pow(calculator_.Get(), secondOperand)); break;
        default: break;
    }

    active_number_ = calculator_.Get();
    ui->l_result->setText(QString::number(active_number_));
    input_number_.clear();
}