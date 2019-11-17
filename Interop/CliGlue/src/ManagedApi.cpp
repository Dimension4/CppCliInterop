#include <CliGlue/Bindings.hpp>

#include <msclr/marshal_cppstd.h>


namespace Glue
{
    public ref class ManagedApi
    {
    public:
        static void SayHello()
        {
			Bindings::SayHello::invokeIfBound();
        }

        static int Add(int x, int y)
        {
			return Bindings::Add::invokeIfBound(x, y).value_or(-1);
        }

        static void Greet(System::String^ name)
        {
			Bindings::Greet::invokeIfBound(
				msclr::interop::marshal_as<std::string>(name)
			);
        }

		static int Accumulate(int x)
		{
			if (!Bindings::Accumulate::isBound())
				throw gcnew System::InvalidOperationException("No accumulator bound");

			return Bindings::Accumulate::invoke(x);
		}

		static void SayGoodbye()
		{
            Bindings::SayGoodbye::invokeIfBound();
		}
    };
}