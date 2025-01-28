#ifndef EXAM_BEVARAGE_H
#define EXAM_BEVARAGE_H

#include "iostream"

class Beverage {
public:
    // Шаблонный метод: Определяет общий алгоритм приготовления напитка
    void prepareBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    virtual ~Beverage() = default;

protected:
    // Методы, которые должны быть реализованы подклассами
    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;

    // Методы с реализацией по умолчанию
    void boilWater() const {
        std::cout << "Boiling water" << std::endl;
    }

    void pourInCup() const {
        std::cout << "Pouring into cup" << std::endl;
    }
};

#endif //EXAM_BEVARAGE_H
