#include <CliGlue/Callbacks.hpp>
#include <CliGlue/TypeTraits.hpp>
#include <CliGlue/Bindings.hpp>

#include <msclr/marshal_cppstd.h>


namespace Glue
{
    public ref class Callbacks
    {
    public:
        static void SayHello()
        {
			Bindings::SayHello::tryInvoke();
        }

        static int Add(int x, int y)
        {
			return Bindings::Add::tryInvoke(x, y).value_or(-1);
        }

        static void Greet(System::String^ name)
        {
			Bindings::Greet::tryInvoke(
				msclr::interop::marshal_as<std::string>(name)
			);
        }

		static int Accumulate(int x)
		{
			using Accumulator = Bindings::Accumulate;

			if (!Accumulator::isBound())
				throw gcnew System::InvalidOperationException("No accumulator bound");

			return Accumulator::invoke(x);
		}

		static int Add(int x, int y)
		{
			return Bindings::Add::tryInvoke(x, y).value_or(-1);
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