#version 330 core

out vec4 FragColor;
in vec2 text_co;
in vec3 color;

uniform int chunk_size;
uniform sampler2D Texture0;

const vec3 gamma = vec3(2.2);
const vec3 inv_gamma = 1 / gamma;

void main()
{
    // Use colorValue to set the color for the fragment
    vec3 texture_color = texture(Texture0,text_co).rgb;
    texture_color =pow(texture_color , gamma);
    texture_color *= color;
    texture_color = pow(texture_color ,inv_gamma);

    FragColor =  vec4(texture_color,1.0f);
}