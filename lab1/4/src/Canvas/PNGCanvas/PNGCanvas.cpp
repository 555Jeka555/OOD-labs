#include "PNGCanvas.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

const std::string& FONTFILEPATH = R"(C:\Volgatech\3course\OOD-labs\lab1\4\src\Canvas\PNGCanvas\font\Minecraft-Regular.ttf)";

gfx::Color gfx::StringToColor(uint32_t color) {
    gfx::Color result{};

    result.r = static_cast<uint8_t>((color >> 24) & 0xFF);
    result.g = static_cast<uint8_t>((color >> 16) & 0xFF);
    result.b = static_cast<uint8_t>((color >> 8) & 0xFF);
    result.a = static_cast<uint8_t>(color & 0xFF);

    return result;
}

void gfx::PNGCanvas::DrawText(double left, double top, double fontSize, const std::string& text)
{
    // Load the font file
    std::ifstream fontFile(FONTFILEPATH, std::ios::binary);
    if (!fontFile.is_open())
    {
        std::cerr << "Failed to open font file!" << std::endl;
        return;
    }

    std::vector<unsigned char> fontBuffer((std::istreambuf_iterator<char>(fontFile)),
                                          std::istreambuf_iterator<char>());
    fontFile.close();

    stbtt_fontinfo font;
    if (!stbtt_InitFont(&font, fontBuffer.data(), stbtt_GetFontOffsetForIndex(fontBuffer.data(), 0)))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }
    float scale = stbtt_ScaleForPixelHeight(&font, fontSize);
    float x = left;
    float y = top;
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    ascent *= scale;
    descent *= scale;

    for (const char* p = text.c_str(); *p; ++p)
    {
        int ch = *p;

        // Get character metrics and position
        int advance, lsb;
        stbtt_GetCodepointHMetrics(&font, ch, &advance, &lsb);

        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&font, ch, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        // Calculate the exact position to place the bitmap
        int bitmapWidth = c_x2 - c_x1;
        int bitmapHeight = c_y2 - c_y1;

        std::vector<unsigned char> charBitmap(bitmapWidth * bitmapHeight);

        // Generate bitmap for the character
        stbtt_MakeCodepointBitmap(&font, charBitmap.data(), bitmapWidth, bitmapHeight, bitmapWidth, scale, scale, ch);

        for (int cy = 0; cy < bitmapHeight; ++cy)
        {
            for (int cx = 0; cx < bitmapWidth; ++cx)
            {
                int srcIndex = cy * bitmapWidth + cx;
                unsigned char alpha = charBitmap[srcIndex];
                if (alpha > 0)
                {
                    PutPixel(static_cast<int>(x) + cx + c_x1, static_cast<int>(y) + cy + ascent + c_y1);
                }
            }
        }
        x += advance * scale;
    }
}

void gfx::PNGCanvas::SaveToFile(const std::string& filename)
{
    stbi_write_png(filename.c_str(), width, height, 4, pixels.data(), width * 4);
}