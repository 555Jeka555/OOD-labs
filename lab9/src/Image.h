#ifndef LAB9_IMAGE_H
#define LAB9_IMAGE_H

#include <cassert>
#include <iostream>
#include <vector>
#include "CoW.h"
#include "Tile.h"
#include "Size.h"

class Image {
public:
    explicit Image(Size size, char color = ' ')
        :   m_size(size),
            m_tiles(size.height, std::vector<CoW<Tile>>(size.width, CoW<Tile>(Tile(color))))
    {}

    [[nodiscard]] Size GetSize() const noexcept {
        return m_size;
    }

    [[nodiscard]] char GetPixel(Point p) const noexcept {
        if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height) {
            return ' ';
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        return m_tiles[tileY][tileX]->GetPixel({ pixelX, pixelY });
    }

    void SetPixel(Point p, char color) {
        if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height) {
            return; // Игнорируем установку цвета, если координаты выходят за пределы
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        // Используем метод Write для изменения тайла
        m_tiles[tileY][tileX].Write([&](Tile& tile) {
            tile.SetPixel({ pixelX, pixelY }, color);
        });
    }

private:
    Size m_size;
    std::vector<std::vector<CoW<Tile>>> m_tiles;
};

#endif //LAB9_IMAGE_H
