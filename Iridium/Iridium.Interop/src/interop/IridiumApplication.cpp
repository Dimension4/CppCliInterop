﻿#include <iridium/interop/IridiumApplication.hpp>
#include <iridium/interop/ApplicationProxy.hpp>
#include <iridium/OperationTemplate.hpp>
#include <iridium/Image.hpp>

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#include <utility>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Media::Imaging;
using namespace System::Threading;
using namespace Iridium::Ui;

using msclr::interop::marshal_as;

namespace ir::interop
{
    IridiumApplication::IridiumApplication()
    {
        m_app = ApplicationProxy::Run();
        m_app->MainViewModel->ExecuteOperation += CreateDelegate<EventHandler<OperationExecutionEventArgs^>>(
            [&](Object^ sender, OperationExecutionEventArgs^ args) 
            {                
                if (m_onExecuteOperation)
                { 
                    auto name = marshal_as<std::string>(args->Name);
                    m_onExecuteOperation(name);
                }
            });
    }

    IridiumApplication::~IridiumApplication() noexcept
    {
        if (static_cast<ApplicationProxy^>(m_app) != nullptr && !hasExited())
            exit();
    }

    IridiumApplication::IridiumApplication(IridiumApplication&& other) noexcept
    {
        operator=(std::move(other));
    }

    IridiumApplication& IridiumApplication::operator=(IridiumApplication&& other) noexcept
    {
        m_app = std::move(other.m_app);
        other.m_app = nullptr;
        return *this;
    }

    IridiumApplication IridiumApplication::run()
    {
        return IridiumApplication{};
    }

    void IridiumApplication::waitExit() const noexcept
    {
        return m_app->WaitExit();
    }

    void IridiumApplication::exit(int exitCode) const noexcept
    {
        m_app->Exit(exitCode);
    }

    void IridiumApplication::showWindow() const noexcept
    {
        m_app->ShowWindow();
    }

    void IridiumApplication::hideWindow() const noexcept
    {
        m_app->HideWindow();
    }

    bool IridiumApplication::hasExited() const noexcept
    {
        return m_app->HasStopped;
    }

    std::vector<OperationTemplate> IridiumApplication::getOperationTemplates() const
    {
        return {};
    }

    void IridiumApplication::setOperationTemplates(std::vector<OperationTemplate> const& operationTemplates) const
    {

    }

    void IridiumApplication::addOperationTemplate(OperationTemplate const& operationTemplate) const
    {

    }

    void IridiumApplication::removeOperationTemplate(std::string_view name) const
    {

    }

    Image IridiumApplication::getImage() const
    {
        return m_app->DispatcherInvoke([&]() { return marshal_as<Image>(m_app->MainViewModel->Image); });
    }

    void IridiumApplication::setImage(Image const& img) const
    {
        m_app->DispatcherInvoke([&]() { m_app->MainViewModel->Image = marshal_as<BitmapSource^>(img); });
    }

    void IridiumApplication::setImage(std::uint8_t const* img, int width, int height, int stride) const
    {

    }

    IridiumApplication::ExecuteOperationCallback& IridiumApplication::onExecuteOperation()
    {
        return m_onExecuteOperation;
    }

    IridiumApplication::ExecuteOperationCallback const& IridiumApplication::onExecuteOperation() const
    {
        return m_onExecuteOperation;
    }
}
