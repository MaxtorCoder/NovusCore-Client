#pragma once
#include <NovusTypes.h>
#include <vector>
#include <functional>

#include "CommandList.h"
#include "Descriptors/GraphicsPipelineDesc.h"
#include "Descriptors/ComputePipelineDesc.h"

namespace Renderer
{
    class Renderer;
    class RenderLayer;
    class RenderGraph;
    class RenderGraphBuilder;

    class IRenderPass
    {
    public:
        virtual bool Setup(RenderGraphBuilder* renderGraphBuilder) = 0;
        virtual void Execute(CommandList& commandList) = 0;
        virtual void DeInit() = 0;
    };

    template <typename PassData>
    class RenderPass : public IRenderPass
    {
    public:
        typedef std::function<bool(PassData&, RenderGraphBuilder&)> SetupFunction;
        typedef std::function<void(PassData&, CommandList&)> ExecuteFunction;
    
        RenderPass(std::string& name, SetupFunction onSetup, ExecuteFunction onExecute)
            : _onSetup(onSetup)
            , _onExecute(onExecute)
        {
            assert(name.length() < 16); // Max length of renderpass names is enforced to 15 chars since we have to store the string internally
            strcpy_s(_name, name.c_str());
        }

    private:
        bool Setup(RenderGraphBuilder* renderGraphBuilder) override
        {
            return _onSetup(_data, *renderGraphBuilder);
        }

        void Execute(CommandList& commandList) override
        {
            commandList.PushMarker(_name, Vector3(0.0f, 0.4f, 0.0f));
            _onExecute(_data, commandList);
            commandList.PopMarker();
        }

        bool ShouldRun() { return _shouldRun; }

        void DeInit() override
        {
            _onSetup = nullptr;
            _onExecute = nullptr;
        }
    private:

    private:
        char _name[16];
        SetupFunction _onSetup;
        ExecuteFunction _onExecute;

        PassData _data;
    };
}