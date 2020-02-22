#pragma once
#include <NovusTypes.h>
#include <vector>

namespace Memory
{
    class Allocator;
}

namespace Renderer
{
    class Renderer;

    struct RenderGraphDesc
    {
        Memory::Allocator* allocator;
    };
}