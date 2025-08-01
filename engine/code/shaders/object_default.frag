#version 330 core

in vec2 texture_coords;
out vec4 object_colour;

uniform sampler2D object_image;
uniform bool is_textured;
uniform vec4 colour;

void main() {
     if (!is_textured) {
         object_colour = colour;
     } else {
         object_colour = colour * texture(object_image, texture_coords);
     }
}
