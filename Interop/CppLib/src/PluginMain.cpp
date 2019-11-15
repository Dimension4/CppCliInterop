#include <CppLib/PluginMain.hpp>
#include <CliGlue/Callbacks.hpp>

#include <iostream>

struct Aggregator
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
    Glue::registerSayHello([counter = 0]() mutable
    {
        std::cout << "Hello for the " << counter++ << " time!\n";
    });

    Aggregator aggregator;

    Glue::registerSomeBinaryFunction([aggregator](int x, int y) mutable
    {
        return aggregator.add(x, y);
    });

    Glue::registerSomeUnaryFunction([](std::string const& x) mutable
    {
        std::cout << x << "\n";
    });
}