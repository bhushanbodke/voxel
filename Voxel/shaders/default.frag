#version 330 core

out vec4 FragColor;

in vec2 text_co;
in flat float voxel_ind;
uniform int chunk_size;
uniform sampler2D Texture0;



void main()
{
	float norm = float(voxel_ind)/float(chunk_size);
    FragColor = vec4(0.5,0.5,norm,1.0f);
}