#ifndef DUCKFUNCTIONS_H
#define DUCKFUNCTIONS_H

#include "Duck.h"

auto CreateQuackNormal = []()
{
    return []() {
        std::cout << "Quack!" << std::endl;
    };
};

auto CreateSqueak = []()
{
    return []()
    {
        std::cout << "Squeak!" << std::endl;
    };
};

auto CreateMuteQuack = []()
{
    return []() {};
};

auto CreateDanceWaltz = []()
{
    return []()
    {
        std::cout << "Waltz!!" << std::endl;
    };
};

auto CreateDanceMinuet = []()
{
    return []()
    {
        std::cout << "Minuet!!" << std::endl;
    };
};

auto CreateNoDance = []()
{
    return []() {};
};

auto CreateFlyWithCounting = []()
{
    int amountDepartures = 0;

    return [amountDepartures]() mutable {
        ++amountDepartures;

        std::cout << "I'm flying! Departure number:" << amountDepartures << std::endl;
    };
};

auto CreateFlyNoWay = []()
{
    return []() {};
};

void DrawDuck(Duck const& duck)
{
    duck.Display();
}

void PlayWithDuck(Duck& duck)
{
    DrawDuck(duck);
    duck.Quack();
    duck.Fly();
    duck.Dance();
    std::cout << std::endl;
}

#endif