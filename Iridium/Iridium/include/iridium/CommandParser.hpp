#pragma once

#include <vector>
#include <optional>
#include <string_view>

namespace ir
{
    std::string_view sanatizeCommand(std::string_view command) noexcept;
    std::optional<std::vector<std::string_view>> parseCommand(std::string_view input) noexcept;
}