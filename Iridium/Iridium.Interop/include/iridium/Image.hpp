#pragma once

#include <vector>
#include <cstdint>

namespace ir
{
    enum class ImageType
    {
        RGB,
        BGR,
        Gray
    };

    struct Image
    {
        int width = 0;
        int height = 0;
        int stride = 0;
        int bitsPerPixel = 0;
        ImageType type = ImageType::RGB;
        std::vector<std::uint8_t> data;
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

        Image outImg = {from->PixelWidth, from->PixelHeight};

        if (from->Format == PixelFormats::Rgb24)
            outImg.type = ImageType::RGB;
        else if (from->Format == PixelFormats::Bgr24)
            outImg.type = ImageType::BGR;
        else if (from->Format == PixelFormats::Gray8)
            outImg.type = ImageType::Gray;

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

        if (from.type == ImageType::BGR)
            fmt = PixelFormats::Bgr24;
        else if (from.type == ImageType::RGB)
            fmt = PixelFormats::Rgb24;
        else if (from.type == ImageType::Gray)
            fmt = PixelFormats::Gray8;

        return BitmapSource::Create(from.width, from.height, 96, 96, fmt, nullptr,
                                    IntPtr(const_cast<std::uint8_t*>(from.data.data())), 
                                    from.data.size(), from.stride);
    }
}

#endif