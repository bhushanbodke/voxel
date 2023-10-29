#pragma once
#include "glad/glad.h"
#include <vector>
#include "glm/gtc/noise.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Settings.h"
#include <iostream>
#include <algorithm>
#include "ShaderClass.h"
#include "player.h"

enum block_types
{
	nothing = 1,
	dirt,
};
struct Vertex
{
	float x;
	float y;
	float z;
	float t1;
	float t2;
	float voxel_id;
	float face_id;
};

class Chunk
{
public:
	// 3d Array of size Settings::chunk_size*Settings::chunk_size*Settings::chunk_size
	std::vector<int> chunk_data;
	glm::vec3 position;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int vao, vbo, ebo;
	float voxel_id, face_id;
	int index = 0;

public:
	Chunk(glm::vec3 pos = {0.0f, 0.0f, 0.0f})
		: position(pos){};

	auto &build_voxels()
	{
		chunk_data.resize(Settings::chunk_size * Settings::chunk_size * Settings::chunk_size, 0);
		glm::vec3 chunk_pos = position * float(Settings::chunk_size);
		for (int x = 0; x < Settings::chunk_size; x++)
		{
			for (int z = 0; z < Settings::chunk_size; z++)
			{
				int wx = x + chunk_pos.x;
				int wz = z + chunk_pos.z;

				int world_height = glm::simplex(glm::vec2(wx, wz) * 0.01f) * 32 + 32;
				int localHeight = std::min(int(world_height - chunk_pos.y), Settings::chunk_size);

				for (int y = 0; y < localHeight; y++)
				{
					int wy = chunk_pos.y + y;
					int index = x + y * Settings::chunk_size + z * Settings::chunk_size * Settings::chunk_size;
					chunk_data[index] = wy + 1;
					Settings::no_voxels++;
				}
			}
		};
		return chunk_data;
	}

	void build_mesh_data()
	{
		get_vertex_data();

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(6 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	bool should_render_face(int x1, int y1, int z1)
	{
		if (0 <= x1 && x1 < Settings::chunk_size && 0 <= y1 && y1 < Settings::chunk_size && 0 <= z1 && z1 < Settings::chunk_size)
		{
			int index = x1 + y1 * Settings::chunk_size + z1 * Settings::chunk_size * Settings::chunk_size;
			if (chunk_data[index] != 0)
			{
				return false;
			}
		}
		return true;
	};

	int push_back(Vertex v)
	{
		vertices.push_back(v);
		return index++;
	}

	void get_vertex_data()
	{
		voxel_id, face_id = 0.0f;
		float halfSize = 0.5f;
		for (float x = 0; x < Settings::chunk_size; x++)
		{
			for (float y = 0; y < Settings::chunk_size; y++)
			{
				for (float z = 0; z < Settings::chunk_size; z++)
				{
					// Front face
					int index = x + y * Settings::chunk_size + z * Settings::chunk_size * Settings::chunk_size;
					voxel_id = chunk_data[index];
					if (chunk_data[index] == 0)
						continue;
					// front
					if (should_render_face(x, y, z - 1))
					{
						unsigned int v1 = push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						unsigned int v2 = push_back({x + halfSize, y - halfSize, (z - halfSize), 1.0f, 0.0f, voxel_id, face_id});
						unsigned int v3 = push_back({x + halfSize, y + halfSize, (z - halfSize), 1.0f, 1.0f, voxel_id, face_id});
						unsigned int v4 = push_back({x - halfSize, y + halfSize, (z - halfSize), 0.0f, 1.0f, voxel_id, face_id});

						indices.insert(indices.end(), {v1, v2, v3, v1, v3, v4});
					}

					// Back face
					if (should_render_face(x, y, z + 1))
					{
						unsigned int v1 = push_back({x - halfSize, y - halfSize, (z + halfSize), 0.0f, 0.0f, voxel_id, face_id});
						unsigned int v2 = push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 0.0f, voxel_id, face_id});
						unsigned int v3 = push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						unsigned int v4 = push_back({x - halfSize, y + halfSize, (z + halfSize), 0.0f, 1.0f, voxel_id, face_id});
						indices.insert(indices.end(), {v1, v2, v3, v1, v3, v4});
					}

					// Right face
					if (should_render_face(x + 1, y, z))
					{
						unsigned int v1 = push_back({x + halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						unsigned int v2 = push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 0.0f, voxel_id, face_id});
						unsigned int v3 = push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						unsigned int v4 = push_back({x + halfSize, y + halfSize, (z - halfSize), 0.0f, 1.0f, voxel_id, face_id});
						indices.insert(indices.end(), {v1, v2, v3, v1, v3, v4});
					}

					// Left face
					if (should_render_face(x - 1, y, z))
					{
						unsigned int v1 = push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						unsigned int v2 = push_back({x - halfSize, y - halfSize, (z + halfSize), 1.0f, 0.0f, voxel_id, face_id});
						unsigned int v3 = push_back({x - halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						unsigned int v4 = push_back({x - halfSize, y + halfSize, (z - halfSize), 1.0f, 1.0f, voxel_id, face_id});

						indices.insert(indices.end(), {v1, v2, v3, v1, v3, v4});
					}

					// Top face
					if (should_render_face(x, y + 1, z))
					{
						unsigned int v1 = push_back({x - halfSize, y + halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						unsigned int v2 = push_back({x + halfSize, y + halfSize, (z - halfSize), 1.0f, 0.0f, voxel_id, face_id});
						unsigned int v3 = push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						unsigned int v4 = push_back({x - halfSize, y + halfSize, (z + halfSize), 0.0f, 1.0f, voxel_id, face_id});
						indices.insert(indices.end(), {v1, v2, v3, v1, v3, v4});
					}

					// Bottom face
					if (should_render_face(x, y - 1, z))
					{
						unsigned int v1 = push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						unsigned int v2 = push_back({x + halfSize, y - halfSize, (z - halfSize), 1.0f, 0.0f, voxel_id, face_id});
						unsigned int v3 = push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						unsigned int v4 = push_back({x - halfSize, y - halfSize, (z + halfSize), 0.0f, 1.0f, voxel_id, face_id});
						indices.insert(indices.end(), {v1, v2, v3, v1, v3, v4});
					}
				}
			}
		}
	}

	void render(Shader &shader, Player &player)
	{
		shader.use();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position * float(Settings::chunk_size));
		glm::mat4 projection = player.get_projection();
		glm::mat4 view = player.Get_view_mat4();

		shader.set_uniform_mat4("MVP", projection * view * model);
		shader.set_uniform_int("chunk_size", Settings::chunk_size);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	};
};
