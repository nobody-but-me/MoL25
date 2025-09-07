#version 330 core

layout (location = 1) in vec2 object_texture;
layout (location = 0) in vec4 object_vertex;

uniform bool threed_object;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

out vec2 texture_coords;

void main()
{
     // NOTE: Likely not the best way to do this.
     if (!threed_object) {
         texture_coords = object_vertex.zw;
         gl_Position = projection * view * transform * vec4(object_vertex.xy, 0.0f, 1.0f);
     } else {
         texture_coords = object_texture.xy;
         gl_Position = projection * view * transform * vec4(object_vertex.xyz, 1.0f);
     }
}