#pragma once

#include <iridium/IridiumInteropApi.hpp>
#include <iridium/interop/GCRoot.hpp>

namespace ir::interop
{
#ifdef _MANAGED
    ref class WpfApplicationWrapper;
#endif

    class IridiumApplication
    {
    public:
        IRIDIUM_INTEROP_API IridiumApplication();
        IRIDIUM_INTEROP_API IridiumApplication(IridiumApplication const&) = delete;
        IRIDIUM_INTEROP_API IridiumApplication& operator=(IridiumApplication const&) = delete;

        IRIDIUM_INTEROP_API void run();
        IRIDIUM_INTEROP_API void waitExit();
        IRIDIUM_INTEROP_API void showWindow();
        IRIDIUM_INTEROP_API void hideWindow();
        
    private:
        GCROOT(WpfApplicationWrapper^) m_app;
    };
}