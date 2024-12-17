#ifndef LAB10_POINT_H
#define LAB10_POINT_H

#pragma once
#include <iostream>

enum class DirectionPoint
{
    LEFT_TOP,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    LEFT_BOTTOM,
};

class Point
{
public:

    Point(double x = 0, double y = 0) : m_x(x), m_y(y) {}

    double m_x;
    double m_y;

    friend std::istream& operator>>(std::istream& inputStream, Point& point)
    {
        inputStream >> point.m_x >> point.m_y;

        return inputStream;
    }

    friend std::ostream& operator<<(std::ostream& outputStream, const Point& point)
    {
        outputStream << point.m_x << " " << point.m_y;

        return outputStream;
    }
};

#endif //LAB10_POINT_H
