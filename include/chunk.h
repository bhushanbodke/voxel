#pragma once
#include <vector>
#include "glm/gtc/noise.hpp"
#include "glm/glm.hpp"

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
	std::vector<std::vector<std::vector<block_types>>> chunk_data;
	glm::vec3 position;
	std::vector<Vertex> vertices;
	unsigned int vao, vbo, ebo;
	float voxel_id, face_id;
	static int chunk_id;

public:
	Chunk(glm::vec3 pos = {0.0f, 0.0f, 0.0f})
		: position(pos) { chunk_id++; };

	void build_voxels()
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
		build_mesh_data();
	}

	void build_mesh_data()
	{
		get_vertex_data();

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

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
		std::cout << "\r"
				  << "[+] Finished Building chunk mesh no " << Chunk::chunk_id << std::endl;
	}

	bool should_render_face(int x1, int y1, int z1)
	{
		if (0 <= x1 && x1 < Settings::chunk_size && 0 <= y1 && y1 < Settings::chunk_size && 0 <= z1 && z1 < Settings::chunk_size)
		{
			if (chunk_data[x1][y1][z1] != nothing)
			{
				return false;
			}
		}
		return true;
	};

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
					if (chunk_data[x][y][z] == nothing)
						continue;
					// front
					if (should_render_face(x, y, z - 1))
					{
						vertices.push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y - halfSize, (z - halfSize), 1.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z - halfSize), 1.0f, 1.0f, voxel_id, face_id});

						vertices.push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z - halfSize), 1.0f, 1.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y + halfSize, (z - halfSize), 0.0f, 1.0f, voxel_id, face_id});
						face_id++;
					}

					// Back face
					if (should_render_face(x, y, z + 1))
					{
						vertices.push_back({x - halfSize, y - halfSize, (z + halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});

						vertices.push_back({x - halfSize, y - halfSize, (z + halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y + halfSize, (z + halfSize), 0.0f, 1.0f, voxel_id, face_id});
						face_id++;
					}

					// Right face
					if (should_render_face(x + 1, y, z))
					{
						vertices.push_back({x + halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});

						vertices.push_back({x + halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z - halfSize), 0.0f, 1.0f, voxel_id, face_id});
						face_id++;
					}

					// Left face
					if (should_render_face(x - 1, y, z))
					{
						vertices.push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y - halfSize, (z + halfSize), 1.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});

						vertices.push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y + halfSize, (z - halfSize), 0.0f, 1.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						face_id++;
					}

					// Top face
					if (should_render_face(x, y + 1, z))
					{
						vertices.push_back({x - halfSize, y + halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z - halfSize), 1.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});

						vertices.push_back({x - halfSize, y + halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y + halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y + halfSize, (z + halfSize), 0.0f, 1.0f, voxel_id, face_id});
						face_id++;
					}

					// Bottom face
					if (should_render_face(x, y - 1, z))
					{
						vertices.push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y - halfSize, (z - halfSize), 1.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});

						vertices.push_back({x - halfSize, y - halfSize, (z - halfSize), 0.0f, 0.0f, voxel_id, face_id});
						vertices.push_back({x + halfSize, y - halfSize, (z + halfSize), 1.0f, 1.0f, voxel_id, face_id});
						vertices.push_back({x - halfSize, y - halfSize, (z + halfSize), 0.0f, 1.0f, voxel_id, face_id});
						face_id++;
					}
					voxel_id++;
				}
			}
		}
	}

	void render(Shader &shader, Player &player)
	{
		shader.use();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 projection = player.get_projection();
		glm::mat4 view = player.Get_view_mat4();

		shader.set_uniform_mat4("MVP", projection * view * model);
		shader.set_uniform_int("chunk_size", Settings::chunk_size);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);
	};
};
int Chunk::chunk_id = 0;
