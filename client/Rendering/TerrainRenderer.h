#pragma once
#include <NovusTypes.h>
#include <array>

#include <Utils/StringUtils.h>
#include <Renderer/Descriptors/ImageDesc.h>
#include <Renderer/Descriptors/DepthImageDesc.h>
#include <Renderer/Descriptors/TextureDesc.h>
#include <Renderer/Descriptors/TextureArrayDesc.h>
#include <Renderer/Descriptors/ModelDesc.h>
#include <Renderer/Descriptors/SamplerDesc.h>
#include <Renderer/ConstantBuffer.h>
#include <Renderer/StorageBuffer.h>

#include "../Gameplay/Map/Chunk.h"
#include "Renderer/InstanceData.h"
#include "ViewConstantBuffer.h"

namespace Terrain
{
    struct Map;

    constexpr u32 NUM_VERTICES_PER_CHUNK = Terrain::CELL_TOTAL_GRID_SIZE * Terrain::MAP_CELLS_PER_CHUNK;
    constexpr u32 NUM_INDICES_PER_CHUNK = 768;
}

namespace Renderer
{
    class RenderGraph;
    class Renderer;
}

class TerrainRenderer
{
public:
    TerrainRenderer(Renderer::Renderer* renderer);

    void Update(f32 deltaTime);

    void AddTerrainDepthPrepass(Renderer::RenderGraph* renderGraph, Renderer::ConstantBuffer<ViewConstantBuffer>* viewConstantBuffer, Renderer::DepthImageID depthTarget, u8 frameIndex);
    void AddTerrainPass(Renderer::RenderGraph* renderGraph, Renderer::ConstantBuffer<ViewConstantBuffer>* viewConstantBuffer, Renderer::ImageID renderTarget, Renderer::DepthImageID depthTarget, u8 frameIndex);
    void AddTerrainDebugPass(Renderer::RenderGraph* renderGraph, Renderer::ConstantBuffer<ViewConstantBuffer>* viewConstantBuffer, Renderer::ImageID textureIDTarget, Renderer::ImageID alphaMapTarget, Renderer::DepthImageID depthTarget, u8 frameIndex);

private:
    void CreatePermanentResources();
    void LoadChunk(Terrain::Map& map, u16 chunkPosX, u16 chunkPosY);
    void LoadChunksAround(Terrain::Map& map, ivec2 middleChunk, u16 drawDistance);

    struct TerrainVertex
    {
        vec4 position = vec4(0, 0, 0, 0);
        vec4 texCoord = vec4(0, 0, 0, 0);
    };

    struct TerrainChunkData
    {
        u32 diffuseIDs[4] = { 0 };
    };

    struct TerrainInstanceData
    {
        Renderer::StorageBuffer<std::array<TerrainVertex, Terrain::NUM_VERTICES_PER_CHUNK>>* vertexBuffer = nullptr;
        Renderer::ConstantBuffer<std::array<TerrainChunkData, Terrain::MAP_CELLS_PER_CHUNK>>* chunkData = nullptr;
    };

private:
    Renderer::Renderer* _renderer;

    Renderer::ModelID _chunkModel = Renderer::ModelID::Invalid();
    std::vector<Renderer::InstanceData> _chunkModelInstances;

    Renderer::ConstantBuffer<std::array<u32, Terrain::MAP_CELLS_PER_CHUNK>>* _terrainInstanceIDs = nullptr;
    
    Renderer::TextureArrayID _terrainColorTextureArray = Renderer::TextureArrayID::Invalid();
    Renderer::TextureArrayID _terrainAlphaTextureArray = Renderer::TextureArrayID::Invalid();

    Renderer::SamplerID _alphaSampler;
    Renderer::SamplerID _colorSampler;
};