#pragma once
#include "Cube.h"
#include "ShaderClass.h"
#include "player.h"
#include <unordered_map>
#include "chunkMesh.h"

class Scene
{
public:
	ChunkMesh chunk;
	Cube cube;
	Shader shader;
	Player player;
	 
	void Init()
	{
		chunk.set_vertex_data();
		shader.SetShader("default");
		player.Init({ 0.0,0.0,50.0f }, 5.0f);
	}

	void render(float delta_time)
	{
		chunk.render(shader, player);
		player.update(delta_time);
	}
};
