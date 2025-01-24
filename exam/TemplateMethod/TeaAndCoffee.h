#ifndef EXAM_TEAANDCOFFEE_H
#define EXAM_TEAANDCOFFEE_H

#include "Bevarage.h"

class Tea : public Beverage {
protected:
    void brew() const override {
        std::cout << "Steeping the tea" << std::endl;
    }

    void addCondiments() const override {
        std::cout << "Adding lemon" << std::endl;
    }
};

// Конкретный класс: Приготовление кофе
class Coffee : public Beverage {
protected:
    void brew() const override {
        std::cout << "Dripping coffee through filter" << std::endl;
    }

    void addCondiments() const override {
        std::cout << "Adding sugar and milk" << std::endl;
    }
};

#endif //EXAM_TEAANDCOFFEE_H
