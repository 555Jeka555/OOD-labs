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
    explicit Image(Size size, uint32_t color = 0xFFFFFF)
        :   m_size(size),
            m_tiles(size.height, std::vector<CoW<Tile>>(size.width, CoW<Tile>(Tile(color))))
    {}

    [[nodiscard]] Size GetSize() const noexcept {
        return m_size;
    }

    [[nodiscard]] uint32_t GetPixel(Point p) const noexcept {
        if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height) {
            return 0xFFFFFF;
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        return m_tiles[tileY][tileX]->GetPixel({ pixelX, pixelY });
    }

    void SetPixel(Point p, uint32_t color) {
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
