#include <CppLib/PluginMain.hpp>
#include <CliGlue/Bindings.hpp>

#include <iostream>

struct Accumulator
{
    int total = 0;

    template <typename ...Args>
    int add(Args... values)
    {
        total = (total + ... + values);
        return total;
    }
};


void pluginMain()
{
    using namespace Glue::Bindings;

    SayHello::bind([]() { std::cout << "Hello!\n"; });
    Greet::bind([](auto const& str) { std::cout << "Hello " << str << "!\n"; });
    SayGoodbye::bind([]() { std::cout << "Goodbye!\n"; });
    Add::bind([](auto a, auto b) { return a + b; });
    
    Accumulator accu;
    Accumulate::bind([accu](auto x) mutable { return accu.add(x); });
}