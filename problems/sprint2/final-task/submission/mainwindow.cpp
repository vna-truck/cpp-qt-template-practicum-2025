#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include "calculator.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    // Цифровые кнопки
    connect(ui->tb_one, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_two, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_three, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_four, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_five, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_six, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_seven, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_eight, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_nine, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_zero, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);

    // Подключение кнопок операций
    connect(ui->tb_add, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
    connect(ui->tb_substract, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
    connect(ui->tb_multiplicate, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
    connect(ui->tb_divide, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
    connect(ui->tb_power, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);

    ResetCalculator();

}

MainWindow::~MainWindow() {
    delete ui;
}

//Ввод цифр
void MainWindow::OnDigitClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString digit = button->text();

    if (input_number_ == "0" && digit != "0") {
        input_number_.clear();
    }

    input_number_ += digit;
    active_number_ = input_number_.toDouble();
    UpdateResult();
}

void MainWindow::UpdateResult() {
    ui->l_result->setText(input_number_.isEmpty() ? QString::number(active_number_) : input_number_);
}

void MainWindow::ResetCalculator()
{
    calculator_.Clear();
    current_operation_ = NO_OPERATION;
    input_number_.clear();
    active_number_ = 0.0;
    ui->l_formula->clear();
    ui->l_result->setText("0");
    ui->l_memory->clear();
}

void MainWindow::PerformOperation() {
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

    QString firstOperand = QString::number(calculator_.GetNumber(), 'g', 12);
    QString secondOperandStr = QString::number(secondOperand, 'g', 12);
    ui->l_formula->setText(QString("%1 %2 %3 =").arg(firstOperand).arg(opSymbol).arg(secondOperandStr));

    switch (current_operation_) {
        case ADDITION: calculator_.Add(secondOperand); break;
        case SUBTRACTION: calculator_.Sub(secondOperand); break;
        case MULTIPLICATION: calculator_.Mul(secondOperand); break;
        case DIVISION:
            if (secondOperand == 0) {
                ui->l_result->setText("Error");
                return;
            }
            calculator_.Div(secondOperand);
            break;
        case POWER: calculator_.Set(std::pow(calculator_.GetNumber(), secondOperand)); break;
        default: break;
    }

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_.clear();
}

void MainWindow::OnOperationClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();

    if (current_operation_ != NO_OPERATION && input_number_.isEmpty()) {
        if (op == "+") current_operation_ = ADDITION;
        else if (op == "−") current_operation_ = SUBTRACTION;
        else if (op == "×") current_operation_ = MULTIPLICATION;
        else if (op == "÷") current_operation_ = DIVISION;
        else if (op == "xʸ") current_operation_ = POWER;

        ui->l_formula->setText(QString("%1 %2").arg(calculator_.GetNumber()).arg(op == "xʸ" ? "^" : op));
        return;
    }

    if (!input_number_.isEmpty()) {
        calculator_.Set(input_number_.toDouble());
        input_number_.clear();
    }

    if (op == "+") {
        current_operation_ = ADDITION;
    }else if (op == "−") {
        current_operation_ = SUBTRACTION;
    }else if (op == "×") {
        current_operation_ = MULTIPLICATION;
    }else if (op == "÷") {
        current_operation_ = DIVISION;
    }else if (op == "xʸ") {
        current_operation_ = POWER;
    }

    ui->l_formula->setText(QString("%1 %2").arg(calculator_.GetNumber()).arg(op == "xʸ" ? "^" : op));
}


void MainWindow::on_tb_reset_clicked() {
    calculator_.Clear();
    current_operation_ = NO_OPERATION;
    input_number_.clear();
    active_number_ = 0.0;
    ui->l_formula->clear();
    ui->l_result->setText("0");
}

void MainWindow::on_tb_equal_clicked() {
    if (current_operation_ == NO_OPERATION) return;

    PerformOperation();
    current_operation_ = NO_OPERATION;
}

void MainWindow::on_tb_negate_clicked() {
    if (!input_number_.isEmpty()) {
        // Если число вводится, меняем знак в строке ввода
        if (input_number_ == "0") return;

        if (input_number_.startsWith('-')) {
            input_number_.remove(0, 1);
        } else {
            input_number_.prepend('-');
        }
        active_number_ = input_number_.toDouble();
    } else {
        // Если число не вводится, меняем знак активного числа
        active_number_ *= -1;
        input_number_ = QString::number(active_number_);
    }
    UpdateResult();
}

void MainWindow::on_tb_backspace_clicked() {
    if (input_number_.isEmpty()) return;

    input_number_.chop(1);
    if (input_number_.isEmpty() || input_number_ == "-") {
        input_number_ = "0";
    }
    active_number_ = input_number_.toDouble();
    UpdateResult();
}


void MainWindow::on_tb_ms_clicked() {
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui->l_memory->setText("M");
}


void MainWindow::on_tb_mr_clicked() {
    if (!memory_saved_) return;

    active_number_ = memory_cell_;
    input_number_ = QString::number(active_number_);
    UpdateResult();
}


void MainWindow::on_tb_mc_clicked() {
    memory_saved_ = false;
    memory_cell_ = 0.0;
    ui->l_memory->clear();
}


void MainWindow::on_tb_comma_clicked() {
    if (input_number_.contains('.')) return;

    if (input_number_.isEmpty()) {
        input_number_ = "0";
    }

    input_number_ += ".";
    UpdateResult();
}

