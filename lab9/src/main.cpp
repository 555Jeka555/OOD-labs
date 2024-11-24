#include <iostream>
#include "Image.h"
#include "ImageService.h"
#include "Drawer.h"

int main() {
    {
        Image img = ImageService::LoadImage(
                " CCCC             \n"
                "CC  CC   ##    ## \n"
                "CC      ####  ####\n"
                "CC  CC   ##    ## \n"
                " CCCC             \n");
        ImageService::Print(img, std::cout);
    }

    std::cout << std::endl;

    {
        Image img({30, 20}, '.');

        Drawer::DrawLine(img, {5, 8}, {15, 1}, '#');
        Drawer::DrawLine(img, {15, 1}, {25, 8}, '#');
        Drawer::DrawLine(img, {5, 8}, {25, 8}, '#');

        Drawer::DrawLine(img, {5, 8}, {5, 18}, '#');
        Drawer::DrawLine(img, {25, 8}, {25, 18}, '#');
        Drawer::DrawLine(img, {5, 18}, {25, 18}, '#');

        Drawer::DrawCircle(img, {15, 13}, 3, '#');

        ImageService::Print(img, std::cout);
    }

    {
        Image img({30, 20}, 0xFFFFFF);

        Drawer::DrawLine(img, {5, 8}, {15, 1}, 0x00FF00);
        Drawer::DrawLine(img, {15, 1}, {25, 8}, 0x00FF00);
        Drawer::DrawLine(img, {5, 8}, {25, 8}, 0x00FF00);

        Drawer::DrawLine(img, {5, 8}, {5, 18}, 0x00FF00);
        Drawer::DrawLine(img, {25, 8}, {25, 18}, 0x00FF00);
        Drawer::DrawLine(img, {5, 18}, {25, 18}, 0x00FF00);

        Drawer::FillCircle(img, {15, 13}, 3, 0x00FFFF);
        Drawer::DrawCircle(img, {15, 13}, 3, 0xFF0000);

        ImageService::Print(img, std::cout);

        std::cout << std::endl;

        ImageService::SaveImageToPPM(img, "house_with_window.ppm");
    }

    return 0;
}
