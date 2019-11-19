#pragma once

#if defined(CPP_LIB_EXPORT)
#   define CPP_LIB_API __declspec(dllexport)
#else
#   define CPP_LIB_API __declspec(dllimport)
#endif