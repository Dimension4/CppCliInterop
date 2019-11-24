#pragma once

#include "LambdaWrapper.hpp"

#include <utility>
#include <type_traits>

namespace ir::interop
{
    using namespace System;
    using namespace System::Windows;
    using namespace System::Threading;
    using namespace Iridium::Ui;

    private ref class ApplicationProxy
    {
    public:
        property IridiumWindowViewModel^ MainViewModel
        {
            IridiumWindowViewModel^ get() { return m_viewModel; }
        }

        property bool HasStopped 
        {
            bool get() { return m_exitSignal->IsSet; }
        }

        static ApplicationProxy^ Run()
        {
            return gcnew ApplicationProxy();
        }

        void WaitExit()
        {
            m_exitSignal->Wait();
        }

        void Exit()
        {
            Exit(0);
        }

        void Exit(int exitCode)
        {
            m_app->Dispatcher->Invoke(gcnew Action<int>(m_app, &Application::Shutdown), exitCode);
            WaitExit();
        }

        void ShowWindow()
        {
            m_app->Dispatcher->Invoke(gcnew Action(m_window, &IridiumWindow::Show));
        }

        void HideWindow()
        {
            m_app->Dispatcher->Invoke(gcnew Action(m_window, &IridiumWindow::Hide));
        }

        template <typename F>
        std::invoke_result_t<F> DispatcherInvoke(F&& func)
        {
            using result_t = std::invoke_result_t<F>;

            if constexpr (std::is_same_v<result_t, void>)
                m_app->Dispatcher->Invoke(CreateDelegate<Action>(std::forward<F>(func)));
            else
                return m_app->Dispatcher->Invoke(CreateDelegate<Func<result_t>>(std::forward<F>(func)));
        }

    private:
        Application^ m_app;
        IridiumWindow^ m_window;
        IridiumWindowViewModel^ m_viewModel = gcnew IridiumWindowViewModel();
        Thread^ m_uiThread = gcnew Thread(gcnew ThreadStart(this, &ApplicationProxy::RunApp));
        ManualResetEventSlim^ m_exitSignal = gcnew ManualResetEventSlim();
        ManualResetEventSlim^ m_startupSignal = gcnew ManualResetEventSlim();

        ApplicationProxy()
        {
            m_uiThread->SetApartmentState(ApartmentState::STA);
            m_uiThread->Start();
            m_startupSignal->Wait();
        }

        void OnStartup(Object^ sender, StartupEventArgs^ args)
        {
            m_viewModel = gcnew IridiumWindowViewModel();
            m_window = gcnew IridiumWindow();
            m_window->IridiumWindowViewModel = m_viewModel;
            m_app->MainWindow = m_window;
            m_window->Show();
            m_startupSignal->Set();
        }

        void RunApp()
        {
            m_app = gcnew Application();
            m_app->Startup += gcnew StartupEventHandler(this, &ApplicationProxy::OnStartup);
            m_app->Run();
            m_exitSignal->Set();
        }
    };
}