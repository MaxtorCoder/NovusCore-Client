#pragma once
#include "BufferBackend.h"

namespace Renderer
{
    template <typename T>
    struct ConstantBuffer
    {
        T resource;

        constexpr size_t GetSize()
        {
            return sizeof(T);
        }

        void Apply(u32 frameIndex)
        {
            backend->Apply(frameIndex, &resource, GetSize());
        }

        void ApplyAll()
        {
            for (u32 i = 0; i < 2; i++)
            {
                Apply(i);
            }
        }

        void* GetDescriptor(u32 frameIndex)
        {
            return backend->GetDescriptor(frameIndex);
        }

        void* GetBuffer(u32 frameIndex)
        {
            return backend->GetBuffer(frameIndex);
        }

        Backend::BufferBackend* backend = nullptr;

    protected:
        ConstantBuffer() {}; // This has to be created through Renderer::CreateConstantBuffer<T>

        friend class Renderer;
    };
}