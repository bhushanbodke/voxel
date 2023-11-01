#version 330 core

out vec4 FragColor;
in vec2 text_co;
in vec3 color;
in vec3 Frag_pos;
in vec3 normal;

uniform int chunk_size;
uniform vec3 light_pos;
uniform sampler2D Texture0;

const vec3 gamma = vec3(2.2);
const vec3 inv_gamma = 1 / gamma;

const vec4 ambient = vec4(0.5 , 0.5 , 0.5 , 1.0);

float cal_diffuse()
{
    vec3 light_dir = normalize(light_pos - Frag_pos);
    float intensity = dot(light_dir,normal);
    return intensity;

}

void main()
{
    // Use colorValue to set the color for the fragment
    vec3 texture_color = texture(Texture0,text_co).rgb;
    texture_color =pow(texture_color , gamma);
    texture_color *= color;
    texture_color = pow(texture_color ,inv_gamma);

    FragColor =  vec4(texture_color,1.0f);
}