#version 330 core

layout (location = 0) in vec3  object_vertex;
layout (location = 1) in vec2 object_texture;
layout (location = 2) in vec3  object_normal;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

out vec2 texture_coords;
out vec3 frag_position;
out vec3 normal;

void main()
{
    gl_Position = projection * view * transform * vec4(object_vertex.xyz, 1.0f);
    frag_position = vec3(transform * vec4(object_vertex.xyz, 1.0f));
    normal = mat3(transpose(inverse(transform))) * object_normal;
    texture_coords = object_texture.xy;
}