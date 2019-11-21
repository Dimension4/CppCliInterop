#pragma once

#include <type_traits>
#include <utility>

namespace ir::interop
{
    namespace internal
    {
        template <typename TLambda>
        ref class LambdaWrapper
        {
        public:
            LambdaWrapper(TLambda&& lambda) : m_func(new TLambda(lambda)) {}

            ~LambdaWrapper()
            {
                this->!LambdaWrapper();
            }

            !LambdaWrapper()
            {
                delete m_func;
            }

            template <typename TReturn, typename... TArgs>
            TReturn Call(TArgs... args)
            {
                return (*m_func)(args...);
            }

        private:
            TLambda* m_func;
        };


        //Support for mutable lambdas

        template <typename TDelegate, typename TLambda, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TLambda&& lambda, TReturn(__thiscall TLambda::*)(TArgs...))
        {
            auto wrapper = gcnew LambdaWrapper<TLambda>(std::forward<TLambda>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TLambda>::Call<TReturn, TArgs...>);
        }

        template <typename TDelegate, typename TLambda, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TLambda&& lambda, TReturn(__clrcall TLambda::*)(TArgs...))
        {
            auto wrapper = gcnew LambdaWrapper<TLambda>(std::forward<TLambda>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TLambda>::Call<TReturn, TArgs...>);
        }

        //Support for immutable lambdas

        template <typename TDelegate, typename TLambda, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TLambda&& lambda, TReturn(__thiscall TLambda::*)(TArgs...) const)
        {
            auto wrapper = gcnew LambdaWrapper<TLambda>(std::forward<TLambda>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TLambda>::Call<TReturn, TArgs...>);
        }

        template <typename TDelegate, typename TLambda, typename TReturn, typename... TArgs>
        TDelegate^ CreateDelegate(TLambda&& lambda, TReturn(__clrcall TLambda::*)(TArgs...) const)
        {
            auto wrapper = gcnew LambdaWrapper<TLambda>(std::forward<TLambda>(lambda));
            return gcnew TDelegate(wrapper, &LambdaWrapper<TLambda>::Call<TReturn, TArgs...>);
        }
    }

    template <typename TDelegate, typename TLambda>
    TDelegate^ CreateDelegate(TLambda&& lambda)
    {
        return internal::CreateDelegate<TDelegate>(std::forward<TLambda>(lambda), &TLambda::operator());
    }
}