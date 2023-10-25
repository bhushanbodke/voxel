#version 330 core

out vec4 FragColor;

in vec2 text_co;
in flat float voxel_id;
in flat float face_id;
uniform int chunk_size;
uniform sampler2D Texture0;


void main()
{
	// Calculate a normalized value based on face_id and chunk_size
    float colorValue = float(face_id) / float(chunk_size * chunk_size * chunk_size *6);
    
    // Use colorValue to set the color for the fragment
    FragColor = vec4(colorValue, 1.0f - colorValue,(1 - colorValue)/colorValue ,1.0f);
}