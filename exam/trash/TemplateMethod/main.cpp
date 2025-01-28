#include "TeaAndCoffee.h"

int main() {
    Tea tea;
    Coffee coffee;

    std::cout << "Making tea..." << std::endl;
    tea.prepareBeverage();

    std::cout << "\nMaking coffee..." << std::endl;
    coffee.prepareBeverage();

    return 0;
}