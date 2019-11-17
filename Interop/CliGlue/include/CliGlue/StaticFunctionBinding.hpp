#pragma once

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
		using SignatureType = TReturn(TArgs...);
		static constexpr decltype(ID) Id = ID;

		static bool isBound() noexcept
		{
			return static_cast<bool>(s_func);
		}

		static TReturn invoke(TArgs... args)
		{
			return s_func(std::forward<TArgs>(args)...);
		}
			
		static auto tryInvoke(TArgs... args) ->
			std::conditional_t<std::is_same_v<TReturn, void>, void, std::optional<TReturn>>
		{
			if constexpr (std::is_same_v<TReturn, void>)
			{
				return isBound()
					? s_func(std::forward<TArgs>(args)...)
					: std::nullopt;
			}
			else
			{
				if (isBound())
					s_func(std::forward<TArgs>(args)...);				
			}
		}

		static void bind(std::function<TReturn(TArgs...)> func) noexcept
		{
			s_func = std::move(func);
		}

		static void unbind() noexcept
		{
			s_func = nullptr;
		}

	private:
		static std::function<TReturn(TArgs...)> s_func;
	};
}