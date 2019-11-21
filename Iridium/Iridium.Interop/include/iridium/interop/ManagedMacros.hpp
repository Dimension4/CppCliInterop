#pragma once

#ifdef _MANAGED

// all the stuff that is only usable in c++/cli code

#   include <gcroot.h>
#   define GCROOT(T) gcroot<T>
#   define FORWARD_DECLARE_MANAGED(T) ref class T

#else

// the drop-in replacements for native c++ code

#   include <cstdint>
class safe_intptr_t
{
    safe_intptr_t() = delete;
    safe_intptr_t(std::nullptr_t) = delete;
    safe_intptr_t(safe_intptr_t const& src) = delete;
    safe_intptr_t& operator= (safe_intptr_t const& src) = delete;
    std::intptr_t ptr;
};

#   define GCROOT(T) safe_intptr_t
#   define FORWARD_DECLARE_MANAGED(T)

#endif