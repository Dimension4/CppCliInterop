#pragma once

#include <CliGlue/StaticFunctionBinding.hpp>

namespace Glue::Bindings
{
	using SayHello = UnmanagedFunctionBinding<0, void()>;
	using Greet = UnmanagedFunctionBinding<1, void(std::string const&)>;
	using SayGoodbye = UnmanagedFunctionBinding<2, void()>;
	using Add = UnmanagedFunctionBinding<3, int(int, int)>;
	using Accumulate = UnmanagedFunctionBinding<4, int(int)>;
}