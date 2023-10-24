#pragma once

#include <string>
#include"glad/glad.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "glm/glm.hpp"
#include "textures.h"

class Shader
{
public:
	GLuint shader_ID;
public:
	Shader():shader_ID(0) {};

	bool SetShader(std::string name)
	{

		std::string vertexShaderSource = load_string("shaders/"+name+".vert");
		std::string fragmentShaderSource = load_string("shaders/" + name + ".frag");

		const char* vert_shader_source = vertexShaderSource.c_str();
		const char* frag_shader_source = fragmentShaderSource.c_str();

		unsigned int vertexShader = compile_shader(vert_shader_source, GL_VERTEX_SHADER);
		unsigned int fragmentShader = compile_shader(frag_shader_source, GL_FRAGMENT_SHADER);
		
		int success;
		char infoLog[512];
		shader_ID = glCreateProgram();
		glAttachShader(shader_ID, vertexShader);
		glAttachShader(shader_ID, fragmentShader);
		glLinkProgram(shader_ID);
		// check for linking errors
		glGetProgramiv(shader_ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader_ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return true;
	}

	void use()
	{
		glUseProgram(shader_ID);
	}

	inline void set_uniform_mat4(std::string name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader_ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
	};
	inline void set_uniform_int(std::string name , int val)
	{
		glUniform1i(glGetUniformLocation(shader_ID, name.c_str()), val);
	}
	inline void set_texture_uniform(Texture & texture)
	{
		glUniform1i(glGetUniformLocation(shader_ID, "Texture" + texture.slot), texture.slot);
	}

private:
	GLuint compile_shader(const char* shader_string, GLuint type)
	{
		int success;
		char infolog[512];
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &shader_string, NULL);
		glCompileShader(shader);
		// check for shader compile errors
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
		}
		return shader;
	};

	std::string load_string(std::string path)
	{
		std::ifstream file(path);
		if (file)
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
		else
		{
			std::cout << "ERROR : opening file at |" << path << "|" << std::endl;
			return "";
		}
	};
};