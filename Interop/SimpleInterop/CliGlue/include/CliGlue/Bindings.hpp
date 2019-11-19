#pragma once

#include "GlueApi.hpp"
#include "UnmanagedFunctionBinding.hpp"

#include <string>

#define CREATE_BINDING(name, signature) \
    using name = UnmanagedFunctionBinding<__LINE__, signature>

namespace Glue::Bindings
{
    CREATE_BINDING(SayHello, void());
    CREATE_BINDING(Greet, void(std::string const&));
    CREATE_BINDING(SayGoodbye, void());
    CREATE_BINDING(Add, int(int, int));
    CREATE_BINDING(Accumulate, int(int));
}

#undef CREATE_BINDING