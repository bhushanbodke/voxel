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
        voxels.resize(
            Settings::world_width * Settings::world_height * Settings::world_depth,
            std::vector<int>(pow(Settings::chunk_size, 3)));
    }
};