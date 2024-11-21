#include <iostream>
#include "CommandHandler.h"
#include "MultiGumballMachine/MultiGumballMachine.h"

int main() {
    try
    {
        multiGumballMachine::MultiGumballMachine multiGumballMachine1 = multiGumballMachine::MultiGumballMachine(1);
        Menu menu{};
        CommandHandler commandHandler = CommandHandler(menu, multiGumballMachine1);

        menu.Run();
        menu.Exit();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
