#ifndef LAB9_TILE_H
#define LAB9_TILE_H

#pragma once
#include <array>
#include <cassert>
#include <cstdint>
#include "Point.h"

class Tile
{
public:
    // Размер тайла 8*8 пикселей.
    constexpr static int SIZE = 8;

    // Конструктор по умолчанию. Заполняет тайл указанным цветом.
    explicit Tile(uint32_t color = 0xFFFFFF) noexcept
    {
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                m_pixels[y][x] = color;
            }
        }

        // -------------- не удалять ------------
        assert(m_instanceCount >= 0);
        ++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    Tile(const Tile& other)
    {
        m_pixels = other.m_pixels; // Копируем пиксели из другого тайла

        // -------------- не удалять ------------
        assert(m_instanceCount >= 0);
        ++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    ~Tile()
    {
        // -------------- не удалять ------------
        --m_instanceCount; // Уменьшаем счётчик тайлов.
        assert(m_instanceCount >= 0);
        // -------------- не удалять ------------
    }

    /**
     * Изменяет цвет пикселя тайла.
     * Если координаты выходят за пределы тайла, метод ничего не делает.
     */

    // TODO форматирование
    void SetPixel(Point p, uint32_t color) noexcept
    {
        if (p.x >= 0 && p.x < SIZE && p.y >= 0 && p.y < SIZE)
        {
            m_pixels[p.y][p.x] = color; // Устанавливаем цвет пикселя
        }
    }

    /**
     * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
     */
    [[nodiscard]] uint32_t GetPixel(Point p) const noexcept
    {
        if (p.x >= 0 && p.x < SIZE && p.y >= 0 && p.y < SIZE)
        {
            return m_pixels[p.y][p.x]; // Возвращаем цвет пикселя
        }
        return 0xFFFFFF; // Возвращаем пробел, если координаты выходят за пределы
    }

    // Возвращает количество экземпляров класса Tile в программе.
    static int GetInstanceCount() noexcept
    {
        // -------------- не удалять ------------
        return m_instanceCount;
        // -------------- не удалять ------------
    }

private:
    // -------------- не удалять ------------
    inline static int m_instanceCount = 0;
    // -------------- не удалять ------------

    std::array<std::array<uint32_t, SIZE>, SIZE> m_pixels{};
};

#endif //LAB9_TILE_H
