﻿#pragma once

#include "../IridiumInteropApi.hpp"
#include "ManagedMacros.hpp"

#include <vector>
#include <functional>
#include <string_view>

namespace ir
{
    struct Image;
    struct OperationTemplate;

    namespace interop
    {
        FORWARD_DECLARE_MANAGED(ApplicationProxy);

        class IridiumApplication
        {
        public:
            using ExecuteOperationCallback = std::function<void(std::string const&)>;

            IRIDIUM_INTEROP_API IridiumApplication(IridiumApplication const&) = delete;
            IRIDIUM_INTEROP_API IridiumApplication& operator=(IridiumApplication const&) = delete;
            IRIDIUM_INTEROP_API IridiumApplication(IridiumApplication&& other) noexcept;
            IRIDIUM_INTEROP_API IridiumApplication& operator=(IridiumApplication&& other) noexcept;
            IRIDIUM_INTEROP_API ~IridiumApplication() noexcept;

            IRIDIUM_INTEROP_API static IridiumApplication run();
            IRIDIUM_INTEROP_API void waitExit() const noexcept;
            IRIDIUM_INTEROP_API void exit(int exitCode = 0) const noexcept;
            IRIDIUM_INTEROP_API void showWindow() const noexcept;
            IRIDIUM_INTEROP_API void hideWindow() const noexcept;
            IRIDIUM_INTEROP_API bool hasExited() const noexcept;
            IRIDIUM_INTEROP_API ExecuteOperationCallback& onExecuteOperation();
            IRIDIUM_INTEROP_API ExecuteOperationCallback const& onExecuteOperation() const;

            IRIDIUM_INTEROP_API std::vector<OperationTemplate> getOperationTemplates() const;
            IRIDIUM_INTEROP_API void setOperationTemplates(std::vector<OperationTemplate> const& operationTemplates) const;
            IRIDIUM_INTEROP_API void addOperationTemplate(OperationTemplate const& operationTemplate) const;
            IRIDIUM_INTEROP_API void removeOperationTemplate(std::string_view name) const;
            IRIDIUM_INTEROP_API Image getImage() const;
            IRIDIUM_INTEROP_API void setImage(Image const& img) const;
            IRIDIUM_INTEROP_API void setImage(std::uint8_t const* img, int width, int height, int stride) const;

        private:
            IridiumApplication();

            GCROOT(ApplicationProxy^) m_app;
            ExecuteOperationCallback m_onExecuteOperation;
        };
    }
}