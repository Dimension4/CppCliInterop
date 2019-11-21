#pragma once

namespace ir::interop
{
    using namespace System;
    using namespace System::Windows;
    using namespace System::Threading;
    using namespace Iridium::Ui;
    
    private ref class WpfApplicationWrapper
    {
    public:
        property IridiumWindowViewModel^ MainViewModel
        {
            IridiumWindowViewModel^ get() { return m_viewModel; }
        };
        
        void Run()
        {
            if (m_uiThread != nullptr && m_uiThread->IsAlive)
                throw gcnew InvalidOperationException("Application is already running.");

            if (m_exitSignal->IsSet)
                throw gcnew InvalidOperationException("Application has already shutdown.");

            m_uiThread = gcnew Thread(gcnew ThreadStart(this, &WpfApplicationWrapper::RunApp));
            m_uiThread->SetApartmentState(ApartmentState::STA);
            m_uiThread->Start();
            m_startupSignal->Wait();
        }

        void WaitExit()
        {
            m_exitSignal->Wait();
        }

        void ShowWindow()
        {
            m_app->Dispatcher->Invoke(gcnew Action(m_window, &IridiumWindow::Show));
        }

        void HideWindow()
        {
            m_app->Dispatcher->Invoke(gcnew Action(m_window, &IridiumWindow::Hide));
        }

    private:
        Application^ m_app;
        IridiumWindow^ m_window;
        IridiumWindowViewModel^ m_viewModel;
        Thread^ m_uiThread;
        ManualResetEventSlim^ m_exitSignal = gcnew ManualResetEventSlim();
        ManualResetEventSlim^ m_startupSignal = gcnew ManualResetEventSlim();

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
            m_app->Startup += gcnew StartupEventHandler(this, &WpfApplicationWrapper::OnStartup);
            m_app->Run();
            m_exitSignal->Set();
        }
    };
}