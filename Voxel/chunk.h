#pragma once
#include <vector>
#include "glm/gtc/noise.hpp"

enum block_types
{
	nothing = 1,
	dirt,
};

class Chunk
{
public:
	// 3d Array of size Settings::chunk_size*Settings::chunk_size*Settings::chunk_size
	std::vector<std::vector<std::vector<block_types>>> chunk_data;
public:
	Chunk()
	{
		chunk_data.resize(Settings::chunk_size, std::vector<std::vector<block_types>>(Settings::chunk_size, std::vector<block_types>(Settings::chunk_size)));
		for (int x = 0; x < Settings::chunk_size; x++)
		{
			for (int y = 0; y < Settings::chunk_size; y++)
			{
				for (int z = 0; z < Settings::chunk_size; z++)
				{
					chunk_data[x][y][z] = dirt; /*glm::simplex(glm::vec3(x,y,z)) < 0.5 ? dirt : nothing;*/
				}
			}
		};
	};
};