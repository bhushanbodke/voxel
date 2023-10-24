#pragma once 
#include "Cube.h"
#include "chunk.h"
#include "player.h"

struct Vertex
{
	float x;
	float y;
	float z;
	float t1;
	float t2;
	float voxel_index;
};

class ChunkMesh
{
public:
	Chunk chunk;
	std::vector<Vertex> vertices;
	std::vector<unsigned int > indices;

	unsigned int vao, vbo, ebo;	
	float index;

public:
	void set_vertex_data()
	{
		get_vertex_data();

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size() , &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	//return true if we should add vertex data of face to the vertex array
	bool should_render_face()
	{

	};

	void get_vertex_data()
	{
		index = 0.0f;
		float halfSize = 0.5f;
		for (int x = 0; x < Settings::chunk_size; x++)
		{
			for (int y = 0; y < Settings::chunk_size; y++)
			{
				for (int z = 0; z < Settings::chunk_size; z++)
				{
					
				}
			}
		}
	}
	void render(Shader& shader, Player& player)
	{
		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 projection = player.get_projection();
		glm::mat4 view = player.Get_view_mat4();

		shader.set_uniform_mat4("MVP", projection * view * model);
		shader.set_uniform_int("chunk_size", Settings::chunk_size);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	};

};
