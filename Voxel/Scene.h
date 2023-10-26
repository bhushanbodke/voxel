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
	Texture cube_border;
	 
	void Init()
	{
		chunk.set_vertex_data();
		shader.SetShader("default");
		player.Init({ 0.0,0.0,50.0f }, 5.0f);
		cube_border.load_texture("assets/block.png");
	}

	void render(float delta_time)
	{
		cube_border.bind_texture();
		shader.set_texture_uniform(cube_border);
		chunk.render(shader, player);
		player.update(delta_time);
	}
};
