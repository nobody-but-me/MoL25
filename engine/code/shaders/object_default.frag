#version 330 core

struct Light {
    vec3 position;
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
};

struct SolidMaterial {
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
    float shine;
    
};
struct TextureMaterial {
    sampler2D diffuse;
    vec3 specular;
    float shine;
};

uniform TextureMaterial texture_material;
uniform SolidMaterial solid_material;
uniform Light object_light;

uniform bool is_textured = false;

uniform vec3 light_position;
uniform vec3 view_position;

uniform vec3 light_colour;
uniform vec3 colour;

in vec2 texture_coords;
in vec3 frag_position;
in vec3 normal;

out vec4 frag_colour;

void main() {
     
     vec3 normalized_normal = normalize(normal);
     
     vec3 light_dir = normalize(object_light.position - frag_position);
     float diff = max(dot(normalized_normal, light_dir), 0.0f);
     
     vec3 reflect_dir = reflect(-light_dir, normalized_normal);
     vec3 view_dir = normalize(view_position - frag_position);
     
     if (is_textured == true) {
	 float spec = pow(max(dot(view_dir, reflect_dir), 0.0), texture_material.shine);
	 
	 vec3 diffuse = object_light.diffuse * diff * vec3(texture(texture_material.diffuse, texture_coords).rgb);
	 vec3 ambient = object_light.ambient * vec3(texture(texture_material.diffuse, texture_coords).rgb);
	 vec3 specular = object_light.specular * (spec * texture_material.specular);
	 
	 vec3 result = ambient + diffuse + specular;
	 frag_colour = vec4(result, 1.0f);
	 // frag_colour = vec4(result, 1.0f) * texture(texture_material.object_image, texture_coords);
	 
     } else {
	 float spec = pow(max(dot(view_dir, reflect_dir), 0.0), solid_material.shine);
	 
	 vec3 specular = object_light.specular * (spec * solid_material.specular);
	 vec3 diffuse = object_light.diffuse * (diff * solid_material.diffuse);
	 vec3 ambient = object_light.ambient * solid_material.ambient;
	 
	 vec3 result = ambient + diffuse + specular;
	 frag_colour = vec4(result, 1.0f);
     }
}
