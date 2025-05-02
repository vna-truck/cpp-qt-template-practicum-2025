#pragma once
#include <string>
#include <cmath>

using Number = double;

class Calculator {
public:
    // Арифметические операции над текущим значением
    void Add(Number value);
    void Subtract(Number value);
    void Multiply(Number value);
    void Divide(Number value);
    void Power(Number value) { current_ = std::pow(current_, value); }

    Number Get() const;
    void Set(Number value);
    void Clear();

    // Работа с памятью
    void Save();
    void Load();
    bool MemoryIsSet() const;

private:
    Number current_ = 0.0;
    Number memory_ = 0.0;
    bool memorySet_ = false;
};