#pragma once
#include "Cube.h"
#include "chunk.h"
#include "ShaderClass.h"
#include "player.h"
#include <unordered_map>
#include "World.h"

class Scene
{
public:
	World world;
	Chunk chunk;
	Cube cube;
	Shader shader;
	Player player;
	Texture cube_border;
	glm::vec3 light_pos;

	void Init()
	{
		world.build_world();
		shader.SetShader("default");
		glm::vec3 world_center;
		world_center.x = Settings::world_width * Settings::chunk_size / 2;
		world_center.y = Settings::world_height * Settings::chunk_size / 2;
		world_center.z = Settings::world_depth * Settings::chunk_size / 2;
		player.Init(world_center, 5.0f);
		cube_border.load_texture("assets/frame.png");
		light_pos = glm::vec3(world_center.x, Settings::world_height + 5, world_center.z);
	}

	void render(float delta_time)
	{
		cube_border.bind_texture();
		shader.set_texture_uniform(cube_border);
		shader.set_uniform_vec3("light_pos", light_pos);
		world.render(shader, player);
		player.update(delta_time);
	}
};
