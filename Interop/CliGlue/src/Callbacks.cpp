#include <CliGlue/Callbacks.hpp>
#include <msclr/marshal_cppstd.h>

#include <string_view>

#define nameof(id) std::string_view(#id)

namespace Glue
{
    public ref class Callbacks
    {
    public:
        static void SayHello()
        {
            auto& func = Internal::getFunction<void>(nameof(SayHello));
            func();
        }

        static int SomeBinaryFunction(int x, int y)
        {
            auto& func = Internal::getFunction<int, int, int>(nameof(SomeBinaryFunction));
            return func(x, y);
        }

        static void SomeUnaryFunction(System::String^ x)
        {
            auto& func = Internal::getFunction<void, std::string>(nameof(SomeUnaryFunction));
            func(msclr::interop::marshal_as<std::string>(x));
        }
    };

#pragma managed(push, off)

    void registerSayHello(std::function<void()> func)
    {
        Internal::getFunction<void>(nameof(SayHello)) = std::move(func);
    }

    void registerSomeBinaryFunction(std::function<int(int, int)> func)
    {
        Internal::getFunction<int, int, int>(nameof(SomeBinaryFunction)) = std::move(func);
    }

    void registerSomeUnaryFunction(std::function<void(std::string)> func)
    {
        Internal::getFunction<void, std::string>(nameof(SomeUnaryFunction)) = std::move(func);
    }

#pragma managed(pop)

}