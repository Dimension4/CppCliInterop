#pragma once

#include <vector>
#include <cstdint>

namespace ir
{
    enum class ImageType
    {
        RGB24,
        BGR24,
        BGR32,
        GRAY8
    };

    struct Image
    {
        int width = 0;
        int height = 0;
        int stride = 0;
        int bitsPerPixel = 0;
        ImageType type = ImageType::RGB24;
        std::vector<std::uint8_t> data;

        operator bool() const noexcept
        {
            return !data.empty();
        }
    };
}

#ifdef _MANAGED

#include <msclr/marshal.h>

namespace msclr::interop
{
    template <>
    ir::Image marshal_as(System::Windows::Media::Imaging::BitmapSource^ const& from)
    {
        using namespace ir;
        using namespace System;
        using namespace Windows;
        using namespace Windows::Media;

        if (from == nullptr)
            return {};

        Image outImg = {from->PixelWidth, from->PixelHeight};
        auto fmt = from->Format;
        if (from->Format == PixelFormats::Rgb24)
            outImg.type = ImageType::RGB24;
        else if (from->Format == PixelFormats::Bgr24)
            outImg.type = ImageType::BGR24;
        else if (from->Format == PixelFormats::Bgr32)
            outImg.type = ImageType::BGR32;
        else if (from->Format == PixelFormats::Gray8)
            outImg.type = ImageType::GRAY8;
        else
            throw gcnew NotSupportedException("The pixel format of the given image is not supported.");

        outImg.bitsPerPixel = from->Format.BitsPerPixel;
        outImg.stride = ((outImg.width * outImg.bitsPerPixel + 31) / 32) * 4;
        outImg.data.resize(outImg.stride * outImg.height);

        from->CopyPixels(Int32Rect::Empty, IntPtr(outImg.data.data()), outImg.data.size(), outImg.stride);
        return outImg;
    }

    template <>
    System::Windows::Media::Imaging::BitmapSource^ marshal_as(ir::Image const& from)
    {
        using namespace ir;
        using namespace System;
        using namespace Windows;
        using namespace Windows::Media;
        using namespace Imaging;

        PixelFormat fmt;

        if (from.type == ImageType::BGR24)
            fmt = PixelFormats::Bgr24;
        else if (from.type == ImageType::BGR32)
            fmt = PixelFormats::Bgr32;
        else if (from.type == ImageType::RGB24)
            fmt = PixelFormats::Rgb24;
        else if (from.type == ImageType::GRAY8)
            fmt = PixelFormats::Gray8;
		else 
			throw gcnew NotImplementedException("Whoops. Forgot that one!");
		
        return BitmapSource::Create(from.width, from.height, 96, 96, fmt, nullptr,
                                    IntPtr(const_cast<std::uint8_t*>(from.data.data())), 
                                    from.data.size(), from.stride);
    }
}

#endif