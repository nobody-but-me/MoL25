#version 330 core

out vec4 frag_colour;

in vec2 texture_coords;
in vec3 frag_position;
in vec3 normal;

uniform bool is_textured = false;
uniform sampler2D object_image;

uniform vec3 light_position;
uniform vec3 view_position;

uniform vec3 light_colour;
uniform vec3 colour;

void main() {
     // this is a mess.
     vec3 light_direction = normalize(light_position - frag_position);
     vec3 normalized_normal = normalize(normal);
     
     float diff = max(dot(normalized_normal, light_direction), 0.0f);
     vec3 diffuse_light = diff * light_colour;
     
     float ambient_strength = 0.1f;
     vec3 ambient = ambient_strength * light_colour;
     
     float specular_strength = 0.5f;
     vec3 view_direction = normalize(view_position - frag_position);
     vec3 reflect_direction = reflect(-light_direction, normalized_normal);
     float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 64);
     vec3 specular_light = specular_strength * spec * light_colour;
     
     vec3 result = (ambient + diffuse_light + specular_light) * colour;
     
     if (is_textured) {
         frag_colour = vec4(result, 1.0f) * texture(object_image, texture_coords);
     } else {
         frag_colour = vec4(result, 1.0f);
     }
}
