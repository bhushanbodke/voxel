#pragma once
#include "Cube.h"
#include "chunk.h"
#include "ShaderClass.h"
#include "player.h"
#include <unordered_map>

class Scene
{
public:
	Chunk chunk;
	Cube cube;
	Shader shader;
	Player player;
	Texture cube_border;

	void Init()
	{
		chunk.build_voxels();
		shader.SetShader("default");
		player.Init({0.0, 0.0, 50.0f}, 5.0f);
		cube_border.load_texture("assets/frame.png");
	}

	void render(float delta_time)
	{
		cube_border.bind_texture();
		shader.set_texture_uniform(cube_border);
		chunk.render(shader, player);
		player.update(delta_time);
	}
};
