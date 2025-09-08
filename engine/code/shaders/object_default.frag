#version 330 core

out vec4 object_colour;
in vec2 texture_coords;

uniform bool is_textured = false;
uniform sampler2D object_image;
uniform vec4 colour;

void main() {
     if (is_textured) {
         object_colour = colour * texture(object_image, texture_coords);
     } else {
         object_colour = colour;
     }
}
