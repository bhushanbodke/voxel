#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texture_co;
layout (location = 2) in float voxel_id;
layout (location = 3) in float Face_Id;

out vec2 text_co;
uniform mat4 MVP;
out flat float face_id;



void main()
{
   gl_Position = MVP *  vec4(aPos, 1.0);
   text_co = texture_co;
   face_id = Face_Id;
};