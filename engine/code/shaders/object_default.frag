#version 330 core

struct Light {
    vec3 position;
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
};

struct Material {
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
    float shine;
};

uniform Material object_material;
uniform Light object_light;

uniform bool is_textured = false;
uniform sampler2D object_image;

uniform vec3 light_position;
uniform vec3 view_position;

uniform vec3 light_colour;
uniform vec3 colour;

in vec2 texture_coords;
in vec3 frag_position;
in vec3 normal;

out vec4 frag_colour;

void main() {
     
     vec3 ambient = object_light.ambient * object_material.ambient;
     
     vec3 normalized_normal = normalize(normal);
     vec3 light_dir = normalize(object_light.position - frag_position);
     float diff = max(dot(normalized_normal, light_dir), 0.0f);
     vec3 diffuse = object_light.diffuse * (diff * object_material.diffuse);
     
     vec3 reflect_dir = reflect(-light_dir, normalized_normal);
     vec3 view_dir = normalize(view_position - frag_position);
     float spec = pow(max(dot(view_dir, reflect_dir), 0.0), object_material.shine);
     vec3 specular = object_light.specular * (spec * object_material.specular);
     
     vec3 result = ambient + diffuse + specular;
     
     // vec3 light_dir = normalize(light_position - frag_position);
     // vec3 view_dir = normalize(view_position - frag_position);
     // vec3 normalized_normal  = normalize(normal);
     
     // float diff = max(dot(normalized_normal, light_dir), 0.0f);
     // vec3 reflect_dir = reflect(-light_dir, normalized_normal);
     
     // float spec = pow(max(dot(view_dir, reflect_dir), 0.0), object_material.shine);
     
     // vec3 specular = object_light.specular * (spec * object_material.specular);
     // vec3 diffuse = object_light.diffuse * (diff * object_material.diffuse);
     // vec3 ambient = object_light.ambient * object_material.ambient;
     
     if (is_textured) {
         frag_colour = vec4(result, 1.0f) * texture(object_image, texture_coords);
     } else {
         frag_colour = vec4(result, 1.0f);
     }
     
     // vec3 light_direction = normalize(light_position - frag_position);
     // vec3 normalized_normal = normalize(normal);
     
     // float diff = max(dot(normalized_normal, light_direction), 0.0f);
     // vec3 diffuse_light = diff * light_colour;
     
     // float ambient_strength = 0.1f;
     // vec3 ambient = ambient_strength * light_colour;
     
     // float specular_strength = 0.5f;
     // vec3 view_direction = normalize(view_position - frag_position);
     // vec3 reflect_direction = reflect(-light_direction, normalized_normal);
     // float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 64);
     // vec3 specular_light = specular_strength * spec * light_colour;
     
     // vec3 result = (ambient + diffuse_light + specular_light) * colour;
}
