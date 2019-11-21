#pragma once

#ifdef _MANAGED
#   include <gcroot.h>
#   define GCROOT(T) gcroot<T>

#else

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

#endif