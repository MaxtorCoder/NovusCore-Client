#pragma once
#include "CommandList.h"
#include "Renderer.h"

namespace Renderer
{
    void CommandList::Execute()
    {
        assert(_markerScope == 0); // We need to pop all markers that we push

        CommandListID commandList = _renderer->BeginCommandList();

        // Execute each command
        for (int i = 0; i < _functions.Count(); i++)
        {
            _functions[i](_renderer, commandList, _data[i]);
        }

        _renderer->EndCommandList(commandList);
    }

    void CommandList::PushMarker(std::string marker, Color color)
    {
        Commands::PushMarker* command = AddCommand<Commands::PushMarker>();
        assert(marker.length() < 16); // Max length of marker names is enforced to 15 chars since we have to store the string internally
        strcpy_s(command->marker, marker.c_str());
        command->color = color;

        _markerScope++;
    }

    void CommandList::PopMarker()
    {
        AddCommand<Commands::PopMarker>();

        assert(_markerScope > 0); // We tried to pop a marker we never pushed
        _markerScope--;
    }

    void CommandList::BeginPipeline(GraphicsPipelineID pipelineID)
    {
        Commands::BeginGraphicsPipeline* command = AddCommand<Commands::BeginGraphicsPipeline>();
        command->pipeline = pipelineID;
    }

    void CommandList::EndPipeline(GraphicsPipelineID pipelineID)
    {
        Commands::EndGraphicsPipeline* command = AddCommand<Commands::EndGraphicsPipeline>();
        command->pipeline = pipelineID;
    }

    void CommandList::SetScissorRect(u32 left, u32 right, u32 top, u32 bottom)
    {
        Commands::SetScissorRect* command = AddCommand<Commands::SetScissorRect>();
        command->scissorRect.left = left;
        command->scissorRect.right = right;
        command->scissorRect.top = top;
        command->scissorRect.bottom = bottom;
    }

    void CommandList::SetViewport(f32 topLeftX, f32 topLeftY, f32 width, f32 height, f32 minDepth, f32 maxDepth)
    {
        Commands::SetViewport* command = AddCommand<Commands::SetViewport>();
        command->viewport.topLeftX = topLeftX;
        command->viewport.topLeftY = topLeftY;
        command->viewport.width = width;
        command->viewport.height = height;
        command->viewport.minDepth = minDepth;
        command->viewport.maxDepth = maxDepth;
    }

    void CommandList::SetConstantBuffer(u32 slot, void* descriptor, size_t frameIndex)
    {
        Commands::SetConstantBuffer* command = AddCommand<Commands::SetConstantBuffer>();
        command->slot = slot;
        command->descriptor = descriptor;
        command->frameIndex = frameIndex;
    }

    void CommandList::SetStorageBuffer(u32 slot, void* descriptor, size_t frameIndex)
    {
        Commands::SetStorageBuffer* command = AddCommand<Commands::SetStorageBuffer>();
        command->slot = slot;
        command->descriptor = descriptor;
        command->frameIndex = frameIndex;
    }

    void CommandList::SetSampler(u32 slot, SamplerID sampler)
    {
        Commands::SetSampler* command = AddCommand<Commands::SetSampler>();
        command->slot = slot;
        command->sampler = sampler;
    }

    void CommandList::SetTexture(u32 slot, TextureID texture)
    {
        Commands::SetTexture* command = AddCommand<Commands::SetTexture>();
        command->slot = slot;
        command->texture = texture;
    }

    void CommandList::SetTextureArray(u32 slot, TextureArrayID textureArray)
    {
        Commands::SetTextureArray* command = AddCommand<Commands::SetTextureArray>();
        command->slot = slot;
        command->textureArray = textureArray;
    }

    void CommandList::SetVertexBuffer(u32 slot, ModelID model)
    {
        Commands::SetVertexBuffer* command = AddCommand<Commands::SetVertexBuffer>();
        command->slot = slot;
        command->modelID = model;
    }

    void CommandList::SetIndexBuffer(ModelID model)
    {
        Commands::SetIndexBuffer* command = AddCommand<Commands::SetIndexBuffer>();
        command->modelID = model;
    }

    void CommandList::SetBuffer(u32 slot, void* buffer)
    {
        Commands::SetBuffer* command = AddCommand<Commands::SetBuffer>();
        command->slot = slot;
        command->buffer = buffer;
    }

    void CommandList::Clear(ImageID imageID, Color color)
    {
        Commands::ClearImage* command = AddCommand<Commands::ClearImage>();                                                                                                       
        command->image = imageID;
        command->color = color;
    }

    void CommandList::Clear(DepthImageID imageID, f32 depth, DepthClearFlags flags, u8 stencil)
    {
        Commands::ClearDepthImage* command = AddCommand<Commands::ClearDepthImage>();                                                                                                      
        command->image = imageID;
        command->depth = depth;
        command->flags = flags;
        command->stencil = stencil;
    }

    void CommandList::Draw(ModelID modelID)
    {
        assert(modelID != ModelID::Invalid());
        Commands::Draw* command = AddCommand<Commands::Draw>();
        command->model = modelID;
    }

    void CommandList::DrawBindless(u32 numVertices, u32 numInstances)
    {
        assert(numVertices > 0);
        assert(numInstances > 0);
        Commands::DrawBindless* command = AddCommand<Commands::DrawBindless>();
        command->numVertices = numVertices;
        command->numInstances = numInstances;
    }

    void CommandList::DrawIndexedBindless(ModelID modelID, u32 numVertices, u32 numInstances)
    {
        assert(modelID != ModelID::Invalid());
        assert(numVertices > 0);
        assert(numInstances > 0);
        Commands::DrawIndexedBindless* command = AddCommand<Commands::DrawIndexedBindless>();
        command->modelID = modelID;
        command->numVertices = numVertices;
        command->numInstances = numInstances;
    }
}