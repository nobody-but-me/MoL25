#version 330 core

layout (location = 1) in vec2 object_texture;
layout (location = 0) in vec3 object_vertex;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

out vec2 texture_coords;

void main()
{
    gl_Position = projection * view * transform * vec4(object_vertex.xyz, 1.0f);
    texture_coords = object_texture.xy;
}