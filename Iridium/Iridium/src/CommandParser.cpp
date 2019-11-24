#include <iridium/CommandParser.hpp>

#include <stack>
#include <array>
#include <utility>

namespace ir
{
    static constexpr auto g_quoteLiteral = '"';
    static constexpr std::string_view g_separator = " \t\n";
    static constexpr auto g_scopeLiterals = std::array
    {
        std::pair{'(', ')'},
        std::pair{'{', '}'},
        std::pair{'[', ']'},
    };

    static constexpr bool isSeparator(char c)
    {
        return g_separator.find(c) != std::string_view::npos;
    };

    std::string_view sanatizeCommand(std::string_view command) noexcept
    {
        auto prevSize = command.size() + 1;
        while (!command.empty() && prevSize > command.size())
        {
            prevSize = command.size();
            for (auto&& [open, close] : g_scopeLiterals)
            {
                if (command.front() == open)
                {
                    command.remove_prefix(1);
                    command.remove_suffix(1);
                }
            }

            if (isSeparator(command.front()))
                command.remove_prefix(1);
            if (isSeparator(command.back()))
                command.remove_suffix(1);

            if (command.front() == g_quoteLiteral)
            {
                command.remove_prefix(1);
                command.remove_suffix(1);
                break;
            }
        }

        return command;
    }

    std::optional<std::vector<std::string_view>> parseCommand(std::string_view input) noexcept
    {
        using namespace std::literals;

        std::stack<char> scopes;
        bool inQuote = false;
        std::vector<std::string_view> result;

        std::size_t elementStart = 0;
        for (std::size_t i = 0; i < input.length(); i++)
        {
            auto c = input[i];
            if (isSeparator(c) && elementStart == i)
            {
                elementStart = i + 1;
            }
            else if (isSeparator(c) && !inQuote && scopes.empty())
            {
                result.push_back(sanatizeCommand(input.substr(elementStart, i - elementStart)));
                elementStart = i + 1;
            }
            else if (c == g_quoteLiteral)
            {
                inQuote = !inQuote;
            }
            else if (!inQuote)
            {
                for (auto&& [open, close] : g_scopeLiterals)
                {
                    if (c == open)
                    {
                        scopes.push(c);
                        break;
                    }
                    else if (c == close)
                    {
                        if (scopes.empty() || scopes.top() != open)
                            return std::nullopt;
                        else
                            scopes.pop();
                        break;
                    }
                }
            }
        }

        if (elementStart < input.length())
            result.push_back(sanatizeCommand(input.substr(elementStart)));

        return inQuote || !scopes.empty()
            ? std::nullopt
            : std::optional(std::move(result));
    }
}