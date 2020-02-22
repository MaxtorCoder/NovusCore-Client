#pragma once
#include <NovusTypes.h>
#include <Utils/StrongTypedef.h>
#include "../RenderStates.h"

namespace Renderer
{
    enum ImageFormat 
    {
        IMAGE_FORMAT_UNKNOWN,
        IMAGE_FORMAT_R32G32B32A32_FLOAT,
        IMAGE_FORMAT_R32G32B32A32_UINT,
        IMAGE_FORMAT_R32G32B32A32_SINT,
        IMAGE_FORMAT_R32G32B32_FLOAT,
        IMAGE_FORMAT_R32G32B32_UINT,
        IMAGE_FORMAT_R32G32B32_SINT,
        IMAGE_FORMAT_R16G16B16A16_FLOAT,
        IMAGE_FORMAT_R16G16B16A16_UNORM,
        IMAGE_FORMAT_R16G16B16A16_UINT,
        IMAGE_FORMAT_R16G16B16A16_SNORM,
        IMAGE_FORMAT_R16G16B16A16_SINT,
        IMAGE_FORMAT_R32G32_FLOAT,
        IMAGE_FORMAT_R32G32_UINT,
        IMAGE_FORMAT_R32G32_SINT,
        IMAGE_FORMAT_R10G10B10A2_UNORM,
        IMAGE_FORMAT_R10G10B10A2_UINT,
        IMAGE_FORMAT_R11G11B10_FLOAT,
        IMAGE_FORMAT_R8G8B8A8_UNORM,
        IMAGE_FORMAT_R8G8B8A8_UNORM_SRGB,
        IMAGE_FORMAT_R8G8B8A8_UINT,
        IMAGE_FORMAT_R8G8B8A8_SNORM,
        IMAGE_FORMAT_R8G8B8A8_SINT,
        IMAGE_FORMAT_R16G16_FLOAT,
        IMAGE_FORMAT_R16G16_UNORM,
        IMAGE_FORMAT_R16G16_UINT,
        IMAGE_FORMAT_R16G16_SNORM,
        IMAGE_FORMAT_R16G16_SINT,
        IMAGE_FORMAT_R32_FLOAT,
        IMAGE_FORMAT_R32_UINT,
        IMAGE_FORMAT_R32_SINT,
        IMAGE_FORMAT_R8G8_UNORM,
        IMAGE_FORMAT_R8G8_UINT,
        IMAGE_FORMAT_R8G8_SNORM,
        IMAGE_FORMAT_R8G8_SINT,
        IMAGE_FORMAT_R16_FLOAT,
        IMAGE_FORMAT_D16_UNORM,
        IMAGE_FORMAT_R16_UNORM,
        IMAGE_FORMAT_R16_UINT,
        IMAGE_FORMAT_R16_SNORM,
        IMAGE_FORMAT_R16_SINT,
        IMAGE_FORMAT_R8_UNORM,
        IMAGE_FORMAT_R8_UINT,
        IMAGE_FORMAT_R8_SNORM,
        IMAGE_FORMAT_R8_SINT
    };

    struct ImageDesc
    {
        std::string debugName = "";
        Vector2i dimensions = Vector2i(0, 0);
        u32 depth = 1;
        ImageFormat format = IMAGE_FORMAT_UNKNOWN;
        SampleCount sampleCount = SAMPLE_COUNT_1;
        Vector4 clearColor = Vector4(0, 0, 0, 1); // TODO: Color class would be better here...
    };

    // Lets strong-typedef an ID type with the underlying type of u16
    STRONG_TYPEDEF(ImageID, u16);
}