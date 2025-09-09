#version 330 core

layout (location = 0) in vec3 object_vertex;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * transform * vec4(object_vertex.xyz, 1.0f);
}