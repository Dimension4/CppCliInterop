#include <CliGlue/GlueApi.hpp>
#include <CliGlue/Bindings.hpp>

#pragma unmanaged

#define INSTANTIATE_BINDING(name)                   \
    template name;                                  \
    decltype(name::s_func) name::s_func = nullptr

namespace Glue
{
    INSTANTIATE_BINDING(Bindings::SayHello);
    INSTANTIATE_BINDING(Bindings::Greet);
    INSTANTIATE_BINDING(Bindings::Add);
    INSTANTIATE_BINDING(Bindings::Accumulate);
    INSTANTIATE_BINDING(Bindings::SayGoodbye);
}