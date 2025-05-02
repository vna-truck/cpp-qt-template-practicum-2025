#include "calculator.h"
#include <cmath>

//Заменяет текущий результат на число n.
void Calculator::Set(Number n){
    current_number_ = n;
}

//Возвращает текущий результат вычислений калькулятора.
//В только что сконструированном калькуляторе этот метод возвращает 0.
Number Calculator::GetNumber() const{
    return current_number_;
}

//Прибавляет число n к текущему результату внутри калькулятора.
void Calculator::Add(Number n) {
    current_number_ += n;
}

//Вычитает число n из текущего результата.
void Calculator::Sub(Number n) {
    current_number_ -= n;
}

//Делит текущий результат на n.
void Calculator::Div(Number n) {
    current_number_ /= n;
}

//Умножает текущий результат на n.
void Calculator::Mul(Number n) {
    current_number_ *= n;
}

//Возводит текущий результат в степень n.
void Calculator::Pow(Number n) {
    current_number_ = std::pow(current_number_, n);
}

//Сохраняет текущий результат в ячейку памяти калькулятора.
void Calculator::Save() {
    memory_number_ = current_number_;
    is_first_mem_ = false;
}

//Загружает число из памяти калькулятора в текущий результат.
void Calculator::Load() {
    current_number_ = memory_number_;

}

//Возвращает true, если ячейка памяти непустая.
bool Calculator::HasMem() const{
    if (!is_first_mem_) {
        return true;
    }
    return false;
}

//Возвращает текущее число, преобразовывая его в std::string функцией std::to_string.
std::string Calculator::GetNumberRepr() const{
    return std::to_string(current_number_);
}

void Calculator::Clear() {
    current_number_ = 0.0;
}
