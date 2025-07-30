#version 330 core

layout (location = 0) in vec4 object_vertex;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main()
{
     gl_Position = projection * view * transform * vec4(object_vertex.xy, 0.0f, 1.0f);
     // gl_Position = vec4(object_vertex.x, object_vertex.y, object_vertex.z, 1.0);
}