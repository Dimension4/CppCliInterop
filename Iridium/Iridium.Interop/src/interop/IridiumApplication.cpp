#include <iridium/interop/IridiumApplication.hpp>
#include <iridium/interop/WpfApplicationWrapper.hpp>

using namespace System;
using namespace System::Windows;
using namespace System::Threading;
using namespace Iridium::Ui;

namespace ir::interop
{
    IridiumApplication::IridiumApplication()
    {
        m_app = gcnew WpfApplicationWrapper();
    }

    void IridiumApplication::run()
    {
        m_app->Run();
    }

    void IridiumApplication::waitExit()
    {
        return m_app->WaitExit();
    }

    void IridiumApplication::showWindow()
    {
        m_app->ShowWindow();
    }

    void IridiumApplication::hideWindow()
    {
        m_app->HideWindow();
    }
}