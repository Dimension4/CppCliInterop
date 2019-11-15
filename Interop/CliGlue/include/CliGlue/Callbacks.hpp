#pragma once

#include <CliGlue/FunctionCache.hpp>
#include <CliGlue/GlueApi.hpp>

#include <string>


namespace Glue
{    
#pragma managed(push, off)

    GLUE_API void registerSayHello(std::function<void()> func);
    GLUE_API void registerSomeBinaryFunction(std::function<int(int, int)> func);
    GLUE_API void registerSomeUnaryFunction(std::function<void(std::string)> func);
    
#pragma managed(pop)
}

