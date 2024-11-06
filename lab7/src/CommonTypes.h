#pragma once

#include <optional>
#include <cstdint>

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

uint32_t OptionalToUint32(const std::optional<RGBAColor>& optionalColor)
{
    if (optionalColor.has_value()) {
        return optionalColor.value();
    }
    return 0xFFFFFFFF;
}