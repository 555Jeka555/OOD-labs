#ifndef LAB10_UUID_H
#define LAB10_UUID_H

#pragma once
#include <iostream>
#include <string>
#include <random>

std::string GenerateUUID()
{
    size_t length = 16;
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    for (size_t i = 0; i < length; ++i)
    {
        result += characters[distribution(generator)];
    }

    return result;
}

#endif //LAB10_UUID_H
