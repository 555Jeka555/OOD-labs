#ifndef LAB5_GRAPHICS_LIB_H
#define LAB5_GRAPHICS_LIB_H

#pragma once
#include <iostream>

namespace graphics_lib
{
    using namespace std;

// Холст для рисования
    class ICanvas
    {
    public:
        // Ставит "перо" в точку x, y
        virtual void MoveTo(int x, int y) = 0;
        // Рисует линию с текущей позиции, передвигая перо в точку x,y
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

// Реализация холста для рисования
    class Canvas : public ICanvas
    {
    public:
        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }
        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }
    };
} // namespace graphics_lib

#endif //LAB5_GRAPHICS_LIB_H
