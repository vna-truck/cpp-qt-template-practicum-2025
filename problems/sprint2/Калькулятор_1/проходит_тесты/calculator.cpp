#include "calculator.h"
#include <cmath>

// Арифметические операции над текущим значением
void Calculator::Add(Number value) {
    current_ += value;
}

void Calculator::Subtract(Number value) {
    current_ -= value;
}

void Calculator::Multiply(Number value) {
    current_ *= value;
}

void Calculator::Divide(Number value) {
    current_ /= value;
}

Number Calculator::Get() const {
    return current_;
}

void Calculator::Set(Number value) {
    current_ = value;
}

void Calculator::Clear() {
    current_ = 0.0;
}

// Работа с памятью
void Calculator::Save() {
    memory_ = current_;
    memorySet_ = true;
}

void Calculator::Load() {
    current_ = memory_;
}

bool Calculator::MemoryIsSet() const {
    return memorySet_;
}
