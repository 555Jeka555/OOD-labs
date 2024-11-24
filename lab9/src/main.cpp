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
        Image img{ { 30, 20 }, '.' };

        Drawer::DrawLine(img, { 3, 2 }, { 26, 5 }, '#');
        Drawer::DrawLine(img, { 26, 5 }, { 21, 18 }, '#');
        Drawer::DrawLine(img, { 21, 18 }, { 3, 2 }, '#');

        ImageService::Print(img, std::cout);
    }

    std::cout << std::endl;

    {
        Image img{ { 30, 20 }, '.' };

        Drawer::DrawCircle(img, { 15, 5 }, 5, '#');

        ImageService::Print(img, std::cout);
    }

    std::cout << std::endl;

    {
        Image img{ { 30, 20 }, '.' };

        Drawer::FillCircle(img, { 15, 5 }, 5, '#');

        ImageService::Print(img, std::cout);
    }
    return 0;
}
