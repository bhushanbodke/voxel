#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texture_co;
layout (location = 2 ) in vec2 normals;
layout (location = 3) in float Voxel_id;
layout (location = 4) in float Face_Id;

out vec2 text_co;
out vec3 color;
out vec3 Frag_pos;
out vec3 normal ;

uniform mat4 MVP;

vec3 hash(float p )
{
    vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1032,0.1030,0.0973));
    p3 += dot(p3 , p3.yzx+33.33);
    return fract((p3.xxy + p3.yzz)*p3.zyx) + 0.05;  
}

void main()
{
    color  = hash(Voxel_id);
    text_co = texture_co;
    Frag_pos = aPos;
    normal = normals;

    gl_Position = MVP *  vec4(aPos, 1.0);
};