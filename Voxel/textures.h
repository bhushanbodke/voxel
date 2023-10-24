#pragma once
#include "string"
#include "glad/glad.h"
#include "stb/stb_image.h"
#include <iostream>

static int slot_no = 0; 

class Texture
{

public:
	unsigned int textureID;
	
	unsigned char* texture_data;
	int slot;

	Texture()
		:slot(slot_no++)
	{};

	bool load_texture(std::string file_path)
	{
		int width, height, bpp;
		stbi_set_flip_vertically_on_load(0);
		texture_data = stbi_load(file_path.c_str(), &width, &height, &bpp, 4);

		if (texture_data)
		{
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(texture_data);

			return true;

		}
		else
		{
			std::cout<<"Error :: error opening file at location || "<<file_path<<std::endl;
			return false;
		}
		
	}
	void bind_texture()
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	void unbind_texture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

};