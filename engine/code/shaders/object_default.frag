#version 330 core

struct Light {
    vec3 position;
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
};

struct Material {
    
    sampler2D object_image;
    
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
    float shine;
    
};
uniform Material object_material;
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
     float spec = pow(max(dot(view_dir, reflect_dir), 0.0), object_material.shine);
     
     if (is_textured == false) {
	 vec3 specular = object_light.specular * (spec * object_material.specular);
	 vec3 diffuse = object_light.diffuse * (diff * object_material.diffuse);
	 vec3 ambient = object_light.ambient * object_material.ambient;
	 
	 vec3 result = ambient + diffuse + specular;
	 frag_colour = vec4(result, 1.0f);
	 
     } else {
	 vec3 diffuse = object_light.diffuse * diff * texture(object_material.object_image, texture_coords).rgb;
	 vec3 ambient = object_light.ambient * texture(object_material.object_image, texture_coords).rgb;
	 vec3 specular = object_light.specular * (spec * object_material.specular);
	 
	 vec3 result = ambient + diffuse + specular;
	 frag_colour = vec4(result, 1.0f);
	 
	 // frag_colour = vec4(result, 1.0f) * texture(object_material.object_image, texture_coords);
     }
}
