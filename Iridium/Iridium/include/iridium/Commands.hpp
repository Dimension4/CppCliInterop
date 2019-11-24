#pragma once

#include <iridium/interop/IridiumApplication.hpp>
#include <iridium/Image.hpp>

#include <functional>
#include <vector>
#include <string_view>
#include <map>

namespace ir::commands
{
    enum class CommandResult
    {
        Success,
        Failure,
        InvalidArguments,
        Exit,
        ExitNoWait
    };

    using CommandFunc = std::function<CommandResult(ir::interop::IridiumApplication&, std::vector<std::string_view>&)>;
    std::map<std::string_view, CommandFunc> const& getCommands() noexcept;
}