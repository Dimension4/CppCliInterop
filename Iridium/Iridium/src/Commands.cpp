#include <iridium/Commands.hpp>

#include <map>
#include <string>
#include <functional>
#include <system_error>
#include <charconv>
#include <iostream>

using namespace ir::interop;

namespace ir::commands
{
    using GetSubCommand = CommandResult(*)(IridiumApplication const&, std::vector<std::string_view>&);
    using SetSubCommand = CommandResult(*)(IridiumApplication&, std::vector<std::string_view>&);

    static CommandResult get(IridiumApplication const& app, std::vector<std::string_view>& args) noexcept;
    static CommandResult getImage(IridiumApplication const& app, std::vector<std::string_view>& args) noexcept;
    static CommandResult set(IridiumApplication& app, std::vector<std::string_view>& args) noexcept;
    static CommandResult setImage(IridiumApplication& app, std::vector<std::string_view>& args) noexcept;
    static CommandResult showWindow(IridiumApplication& app, std::vector<std::string_view>& args) noexcept;
    static CommandResult hideWindow(IridiumApplication& app, std::vector<std::string_view> const& args) noexcept;
    static CommandResult exitApp(IridiumApplication& app, std::vector<std::string_view> const& args) noexcept;
    static CommandResult help(IridiumApplication const& app, std::vector<std::string_view> const& args) noexcept;

    static std::map<std::string, Image> g_imageCache;
    static std::map<std::string_view, GetSubCommand> g_getCommands
    {
        { "image", &getImage }
    };
    static std::map<std::string_view, SetSubCommand> g_setCommands
    {
        { "image", &setImage }
    };
    static std::map<std::string_view, CommandFunc> g_commands
    {
        { "get", &get },
        { "set", &set },
        { "show", &showWindow },
        { "hide", &hideWindow },
        { "exit", &exitApp },
        { "help", &help },
    };

    std::map<std::string_view, CommandFunc> const& getCommands() noexcept
    {
        return g_commands;
    }

    static CommandResult get(IridiumApplication const& app, std::vector<std::string_view>& args) noexcept
    {
        if (args.empty())
            return CommandResult::InvalidArguments;

        if (auto it = g_getCommands.find(args[0]); it != g_getCommands.end())
        {
            args.erase(args.begin());
            return it->second(app, args);
        }

        return CommandResult::InvalidArguments;
    }

    static CommandResult getImage(IridiumApplication const& app, std::vector<std::string_view>& args) noexcept
    {
        if (args.size() != 1)
            return CommandResult::InvalidArguments;
        
        if (auto img = app.getImage(); img)
        {
            g_imageCache[std::string(args[0])] = img;
            return CommandResult::Success;
        }

        return CommandResult::Failure;
    }

    static CommandResult set(IridiumApplication& app, std::vector<std::string_view>& args) noexcept
    {
        if (args.empty())
            return CommandResult::InvalidArguments;

        if (auto it = g_setCommands.find(args[0]); it != g_setCommands.end())
        {
            args.erase(args.begin());
            return it->second(app, args);
        }

        return CommandResult::InvalidArguments;
    }

    static CommandResult setImage(IridiumApplication& app, std::vector<std::string_view>& args) noexcept
    {
        if (args.size() != 1)
            return CommandResult::InvalidArguments;

        if (auto it = g_imageCache.find(std::string(args[0])); it != g_imageCache.end())
        {
            app.setImage(it->second);
            return CommandResult::Success;
        }

        return CommandResult::Failure;
    }

    static CommandResult showWindow(IridiumApplication& app, std::vector<std::string_view>& args) noexcept
    {
        if (!args.empty())
            return CommandResult::InvalidArguments;

        app.showWindow();
        return CommandResult::Success;
    }

    static CommandResult hideWindow(IridiumApplication& app, std::vector<std::string_view> const& args) noexcept
    {
        if (!args.empty())
            return CommandResult::InvalidArguments;

        app.hideWindow();
        return CommandResult::Success;
    }

    static CommandResult exitApp(IridiumApplication& app, std::vector<std::string_view> const& args) noexcept
    {
        constexpr auto ok = std::errc{};

        int exitCode = 0;
        if (args.size() > 1 ||
            !args.empty() && std::from_chars(args[0].data(), args[0].data() + args[0].length(), exitCode).ec != ok)
            return CommandResult::InvalidArguments;

        app.exit(exitCode);
        return CommandResult::ExitNoWait;
    }

    template <typename Lookup>
    void printCommands(Lookup const& commands, std::string const& indention)
    {
        for (auto&& [name, _] : commands)
        {
            std::cout << indention << name << "\n";
            if (name == "get")
                printCommands(g_getCommands, indention + "  ");
            if (name == "set")
                printCommands(g_setCommands, indention + "  ");
        }
    }

    static CommandResult help(IridiumApplication const& app, std::vector<std::string_view> const& args) noexcept
    {
        std::cout << "List of available commands:\n";
        printCommands(getCommands(), "  ");

        return CommandResult::Success;
    }
}