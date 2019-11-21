#pragma once

#ifdef IRIDIUM_INTEROP_EXPORTS
#   define IRIDIUM_INTEROP_API __declspec(dllexport)
#else
#   define IRIDIUM_INTEROP_API __declspec(dllimport)
#endif