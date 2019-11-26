#pragma once

#include <type_traits>
#include <utility>

namespace ir::interop
{
    namespace internal
    {
        template <typename TFunc>
        ref class LambdaWrapper
        {
        public:
            LambdaWrapper(TFunc&& lambda) : m_func(new TFunc(std::move(lambda))) {}

            ~LambdaWrapper()
            {
                this->!LambdaWrapper();
            }

            !LambdaWrapper()
            {
                delete m_func;
            }

            template <typename TReturn, typename... TArgs>
            TReturn Call(TArgs&&... args)
            {
                return (*m_func)(std::forward<TArgs>(args)...);
            }

        private:
            TFunc* m_func;
        };


        //Support for mutable lambdas

        template <typename TDelegate, typename TFunc, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TFunc&& lambda, TReturn(__thiscall TFunc::*)(TArgs...))
        {
            auto wrapper = gcnew LambdaWrapper<TFunc>(std::forward<TFunc>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TFunc>::Call<TReturn, TArgs...>);
        }

        template <typename TDelegate, typename TFunc, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TFunc&& lambda, TReturn(__clrcall TFunc::*)(TArgs...))
        {
            auto wrapper = gcnew LambdaWrapper<TFunc>(std::forward<TFunc>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TFunc>::Call<TReturn, TArgs...>);
        }

        //Support for immutable lambdas

        template <typename TDelegate, typename TFunc, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TFunc&& lambda, TReturn(__thiscall TFunc::*)(TArgs...) const)
        {
            auto wrapper = gcnew LambdaWrapper<TFunc>(std::forward<TFunc>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TFunc>::Call<TReturn, TArgs...>);
        }

        template <typename TDelegate, typename TFunc, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TFunc&& lambda, TReturn(__clrcall TFunc::*)(TArgs...) const)
        {
            auto wrapper = gcnew LambdaWrapper<TFunc>(std::forward<TFunc>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TFunc>::Call<TReturn, TArgs...>);
        }
    }

    template <typename TDelegate, typename TFunc>
    TDelegate^ CreateDelegate(TFunc&& lambda)
    {
        return internal::CreateDelegate<TDelegate>(std::forward<TFunc>(lambda), &TFunc::operator());
    }

#pragma managed(push, off)

    template <typename TFunc, typename TWrapped = std::invoke_result_t<TFunc>>
    auto WrapReturnValue(TFunc&& func, TWrapped& returnValue)
    {
        return [f = std::forward<TFunc>(func), &returnValue]()
        {
            returnValue = f();
        };
    }

#pragma managed(pop)
}