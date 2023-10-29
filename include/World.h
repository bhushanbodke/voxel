#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "chunk.h"
#include "Settings.h"
#include "ShaderClass.h"
#include "player.h"
#include <thread>

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
            std::vector<int>(Settings::chunk_size * Settings::chunk_size * Settings::chunk_size));
    }

    void build_world()
    {
        std::vector<std::thread> threads;
        for (int x = 0; x < Settings::world_width; x++)
        {
            for (int y = 0; y < Settings::world_height; y++)
            {
                for (int z = 0; z < Settings::world_depth; z++)
                {
                    threads.push_back(std::thread(&World::genrate_chunks, this, x, y, z));
                }
            }
        }
        for (auto &thread : threads)
        {
            thread.join();
        }

        build_mesh_data();
    }

    void genrate_chunks(int x, int y, int z)
    {
        int chunk_index = x + y * Settings::world_width + z * Settings::world_width * Settings::world_height;
        chunks[chunk_index] = Chunk({x, y, z});

        voxels[chunk_index] = chunks[chunk_index].build_voxels();

        chunks[chunk_index].chunk_data = voxels[chunk_index];
    }

    void build_mesh_data()
    {
        for (auto &chunk : chunks)
        {
            chunk.build_mesh_data();
        }
    };
    void render(Shader &shader, Player &player)
    {
        for (auto &chunk : chunks)
        {
            chunk.render(shader, player);
        }
    };
};
