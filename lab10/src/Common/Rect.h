#ifndef LAB10_RECT_H
#define LAB10_RECT_H

template <typename T>
struct Rect
{
    T left;
    T top;
    T width;
    T height;

    bool operator==(const Rect& rhs) const
    {
        return left == rhs.left && top == rhs.top && width == rhs.width && height == rhs.height;
    }
};

typedef Rect<double> RectD;

#endif //LAB10_RECT_H
