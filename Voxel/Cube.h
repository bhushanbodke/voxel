#pragma once
#include <glad/glad.h>
#include <vector>
#include "GLFW/glfw3.h"
#include "ShaderClass.h"
#include "camera.h"
#include "textures.h"

class Cube
{
public:
	Shader shader;
	unsigned int vao, vbo, ebo;

public:

	Cube()
		:vao(0), vbo(0), ebo(0)
	{};
	void set_vertex_data()
	{

		std::vector<float> vertices = {
			// Front face
		   -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  // Bottom-left
			0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  // Bottom-right
			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  // Top-right
		   -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  // Top-left

		   // Back face
		  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // Bottom-left
		   0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // Bottom-right
		   0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  // Top-right
		  -0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  // Top-left
		};

		std::vector<unsigned int> indices = {
			// Front face
			0, 1, 2,  // First triangle
			2, 3, 0,  // Second triangle

			// Back face
			4, 5, 6,  // First triangle
			6, 7, 4,  // Second triangle

			// Left face
			4, 0, 3,  // First triangle
			3, 7, 4,  // Second triangle

			// Right face
			1, 5, 6,  // First triangle
			6, 2, 1,  // Second triangle

			// Top face
			3, 2, 6,  // First triangle
			6, 7, 3,  // Second triangle

			// Bottom face
			0, 1, 5,  // First triangle
			5, 4, 0   // Second triangle
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int ) * indices.size(), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);					
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		
	}

	void render(Shader& shader , Camera& camera)
	{
		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 projection = camera.get_projection();
		glm::mat4 view = camera.Get_view_mat4();

		shader.set_uniform_mat4("MVP", projection*view*model);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};