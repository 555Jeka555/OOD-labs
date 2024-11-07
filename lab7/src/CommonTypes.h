#ifndef LAB7_COMMONTYPES_H
#define LAB7_COMMONTYPES_H

template <typename T>
struct Rect
{
    T left;
    T top;
    T width;
    T height;
};

typedef Rect<double> RectD;
typedef uint32_t RGBAColor;

#endif //LAB7_COMMONTYPES_H
