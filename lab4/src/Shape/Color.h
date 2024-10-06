#ifndef LAB4_COLOR_H
#define LAB4_COLOR_H

#include <map>

enum class Color
{
    GREEN,
    RED,
    BLUE,
    YELLOW,
    PINK,
    BLACK,
};

const std::map<Color, uint32_t> colorsToHEX = {
        {Color::GREEN, 0xFF00FF00FF},
        {Color::RED, 0xFFFF0000FF},
        {Color::BLUE, 0xFF0000FFFF},
        {Color::YELLOW, 0xFFFFFF00FF},
        {Color::PINK, 0xFFFFC0CBFF},
        {Color::BLACK, 0xFF000000FF}
};

const std::map<std::string, Color> stringToColor = {
        {"green", Color::GREEN},
        {"red", Color::RED},
        {"blue", Color::BLUE},
        {"yellow", Color::YELLOW},
        {"pink", Color::PINK},
        {"black", Color::BLACK}
};

uint32_t convertColorToHEX(Color color)
{
    return colorsToHEX.at(color);
}

Color convertToColor(const std::string& colorStr)
{
    return stringToColor.at(colorStr);
}

#endif //LAB4_COLOR_H
