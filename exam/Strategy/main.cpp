#include <iostream>
#include <memory>

// Шаг 1: Интерфейс стратегии
class Operation {
public:
    virtual int execute(int a, int b) const = 0;
    virtual ~Operation() = default;
};

// Шаг 2: Конкретные стратегии
class Addition : public Operation {
public:
    int execute(int a, int b) const override {
        return a + b;
    }
};

class Subtraction : public Operation {
public:
    int execute(int a, int b) const override {
        return a - b;
    }
};

class Multiplication : public Operation {
public:
    int execute(int a, int b) const override {
        return a * b;
    }
};

// Шаг 3: Класс, использующий стратегию
class Calculator {
private:
    std::unique_ptr<Operation> operation; // Указатель на стратегию

public:
    // Устанавливаем стратегию
    void setOperation(std::unique_ptr<Operation> op) {
        operation = std::move(op);
    }

    // Выполняем операцию с использованием текущей стратегии
    int calculate(int a, int b) const {
        if (operation) {
            return operation->execute(a, b);
        } else {
            throw std::runtime_error("Operation not set");
        }
    }
};

// Шаг 4: Использование
int main() {
    Calculator calculator;

    // Используем стратегию сложения
    calculator.setOperation(std::make_unique<Addition>());
    std::cout << "10 + 5 = " << calculator.calculate(10, 5) << std::endl;

    // Используем стратегию вычитания
    calculator.setOperation(std::make_unique<Subtraction>());
    std::cout << "10 - 5 = " << calculator.calculate(10, 5) << std::endl;

    // Используем стратегию умножения
    calculator.setOperation(std::make_unique<Multiplication>());
    std::cout << "10 * 5 = " << calculator.calculate(10, 5) << std::endl;

    return 0;
}