#version 330 core

struct Light {
    vec4 vector;
    
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
    
    float quadratic;
    float constant;
    float linear;
};

struct SolidMaterial {
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
    float shine;
    
};
struct TextureMaterial {
    sampler2D specular;
    sampler2D diffuse;
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
     vec3 light_direction;
     if (object_light.vector.w == 0.0f)      light_direction = normalize(-object_light.vector.xyz);
     else if (object_light.vector.w == 1.0f) light_direction = normalize(object_light.vector.xyz - frag_position);
     
     vec3 norm = normalize(normal);
     
     vec3 view_dir = normalize(view_position - frag_position);
     vec3 reflect_dir = reflect(-light_direction, norm);
     float diff = max(dot(norm, light_direction), 0.0f);
     
     float distance = length(object_light.vector.xyz - frag_position);
     float attenuation = 1.0f / (object_light.constant + object_light.linear * distance + object_light.quadratic * (distance * distance));
     
     vec3 result;
     
     if (is_textured == true) {
         float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), texture_material.shine);
	 
	 vec3 specular = object_light.specular * spec * texture(texture_material.specular, texture_coords).rgb;
	 vec3 diffuse  = object_light.diffuse  * diff * texture(texture_material.diffuse , texture_coords).rgb;
	 vec3 ambient  = object_light.ambient         * texture(texture_material.diffuse , texture_coords).rgb;
	 
	 specular *= attenuation;
	 diffuse  *= attenuation;
	 ambient  *= attenuation;
	 
	 result = ambient + diffuse + specular;
	 
     } else {
         float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), solid_material.shine);
	 
	 vec3 specular = object_light.specular * (spec * solid_material.specular);
	 vec3 diffuse  = object_light.diffuse  * (diff * solid_material.diffuse );
	 vec3 ambient  = object_light.ambient  * (solid_material.ambient        );
	 
	 specular *= attenuation;
	 diffuse  *= attenuation;
	 ambient  *= attenuation;
	 
	 result = ambient + diffuse + specular;
	 
     }
     frag_colour = vec4(result, 1.0f);
}

