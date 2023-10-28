#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "chunk.h"
#include "Settings.h"

class World
{
public:
    std::vector<Chunk> chunks;
    std::vector<std::vector<int>> voxels;

public:
    World()
    {
        chunks.resize(Settings::world_width * Settings::world_height * Settings::world_depth);

        voxels.resize(
            Settings::world_width * Settings::world_height * Settings::world_depth,
            std::vector<int>(pow(Settings::chunk_size, 3)));

        build_world();
        build_world_mesh();
    }

    void build_world()
    {
        for (int x = 0; x < Settings::world_width; x++)
        {
            for (int y = 0; y < Settings::world_height; y++)
            {
                for (int z = 0; z < Settings::world_depth; z++)
                {
                    Chunk chunk = Chunk({x, y, z});
                    int chunk_index = x + y * Settings::world_width + z * Settings::world_width * Settings::world_height;
                    chunks[chunk_index] = chunk;

                    voxels[chunk_index] = chunks[chunk_index].build_voxels();

                    chunks[chunk_index] = voxels[chunk_index];
                }
            }
        }
    }
    void build_world_mesh()
    {
        for (auto &chunk : chunks)
        {
            ChunkMesh
        }
    }
};