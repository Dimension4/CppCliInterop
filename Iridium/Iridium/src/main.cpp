#include <iridium/interop/IridiumApplication.hpp>

#include <iostream>
#include <string>

int main()
{
    ir::interop::IridiumApplication app;
    app.run();
    
    std::string input;
    while (std::getline(std::cin, input) && !input.empty())
    {
        if (input == "show")
            app.showWindow();
        else if (input == "hide")
            app.hideWindow();
    }

    app.waitExit();
    return 0;
}