#include <iridium/interop/IridiumApplication.hpp>
#include <iridium/Image.hpp>
#include <iridium/CommandParser.hpp>
#include <iridium/Commands.hpp>

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <charconv>

using namespace ir;
using namespace ir::interop;
using ir::commands::CommandResult;

int main()
{
    auto app = IridiumApplication::run();
    app.onExecuteOperation() = [](auto const& name) { std::cout << "Execute that \"" << name << "\" operation!\n"; };

    auto const& commands = commands::getCommands();

    std::cout << "Enter a command to execute (type \"help\" for help).\n\n";

    std::string input;

    while (!app.hasExited() && std::getline(std::cin, input))
    {
        auto parsedInput = parseCommand(input);

        if (!parsedInput)
        {
            std::cout << "Invalid syntax.\n";
            continue;
        }

        auto& arguments = *parsedInput;

        if (arguments.empty())
            continue;

        auto command = arguments[0];

        if (auto it = commands.find(command); it != commands.end())
        {
            arguments.erase(arguments.begin());
            auto res = it->second(app, arguments);

            if (res == CommandResult::Failure)
                std::cout << "Command failed.\n";
            else if (res == CommandResult::InvalidArguments)
                std::cout << "Invalid arguments.\n";
            else if (res == CommandResult::Exit)
                break;
            else if (res == CommandResult::ExitNoWait)            
                app.exit();
        }
        else
        {
            std::cout << "Unknown command.\n";
        }
    }

    if (!app.hasExited())
    {
        std::cout << "Waiting for application exit...\n";
        app.waitExit();
    }
    return 0;
}