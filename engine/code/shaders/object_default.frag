#version 330 core

in vec2 texture_coords;
out vec4 object_colour;

uniform vec4 colour;

void main() {
     object_colour = colour;
}
