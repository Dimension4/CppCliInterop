#include <iridium/interop/IridiumApplication.hpp>
#include <iridium/Image.hpp>

#include <iostream>
#include <string>

int main()
{
    auto app = ir::interop::IridiumApplication::run();    

    std::cout << "Type \"show\" or \"hide\" to show or hide the window\n\n";

    std::string input;
    ir::Image img;

    while (std::getline(std::cin, input) && !input.empty() && !app.hasStopped())
    {
        if (input == "show")
            app.showWindow();
        else if (input == "hide")
            app.hideWindow();
        else if (input == "get image")
            img = app.getImage();
        else if (input == "set image" && !img.data.empty())
            app.setImage(img);
    }

    std::cout << "Waiting for application exit...\n";
    app.waitExit();
    return 0;
}