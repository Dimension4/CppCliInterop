#pragma once

#if defined(GLUE_EXPORT)
#   define GLUE_API __declspec(dllexport)
#else
#   define GLUE_API __declspec(dllimport)
#endif