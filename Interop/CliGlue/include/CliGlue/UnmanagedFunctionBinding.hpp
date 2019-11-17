#pragma once

#include "GlueApi.hpp"

#include <functional>
#include <utility>
#include <optional>

namespace Glue
{
    template <auto ID, typename TReturn, typename... TArgs>
    class UnmanagedFunctionBinding;

    template <auto ID, typename TReturn, typename... TArgs>
    class UnmanagedFunctionBinding<ID, TReturn(TArgs...)>
    {
    public:
        UnmanagedFunctionBinding() = delete;

        using FunctionType = std::function<TReturn(TArgs...)>;
        static constexpr decltype(ID) Id = ID;

        GLUE_API static bool isBound() noexcept
        {
            return static_cast<bool>(s_func);
        }

        GLUE_API static TReturn invoke(TArgs... args)
        {
            return s_func(std::forward<TArgs>(args)...);
        }

        GLUE_API static auto invokeIfBound(TArgs... args) ->
            std::conditional_t<std::is_same_v<TReturn, void>, void, std::optional<TReturn>>
        {
            if constexpr (std::is_same_v<TReturn, void>)
            {
                if (isBound())
                    s_func(std::forward<TArgs>(args)...);
            }
            else
            {
                return isBound()
                    ? std::make_optional(s_func(std::forward<TArgs>(args)...))
                    : std::nullopt;
            }
        }

        GLUE_API static void bind(std::function<TReturn(TArgs...)> func) noexcept
        {
            s_func = std::move(func);
        }

        GLUE_API static void unbind() noexcept
        {
            s_func = nullptr;
        }

    private:
        static FunctionType s_func;
    };
}