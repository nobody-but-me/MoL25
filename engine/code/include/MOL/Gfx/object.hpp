
#ifndef OBJECTS_H
#define OBJECTS_H

#include <molson.h>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>


// NOTE: these are unsafe structs. The default access to struct members is public, which means that crucial members like vbo, vao, ebo and others can easily be changed, breaking the renderer system and leading to unexpected behaviours. Members like vao, vbo and ebo need to be private.

typedef struct
{
    float outer_radius;
    float radius;
    
    glm::vec3 direction;
    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    
    float quadratic;
    float constant;
    float linear;
    
    Shader *object_shader;
    
} LightMaterial;
typedef struct
{
    
    Texture specular_map;
    Texture texture;
    
    std::string specular_map_path = "";
    std::string texture_path = "";
    
    bool specular_map_alpha;
    bool alpha;
    
    float shininess = 32.0f;
    
    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    
} Material;

typedef struct
{
    
    int light_move_type;
    int light_type;
    
    unsigned int light_vao;
    unsigned int indices;
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    
    bool initialized;
    
    glm::mat4 transform;
    
    LightMaterial light_material;
    Material object_material;
    
    std::string name;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    glm::vec4 colour;
    
} Atom;

#endif//OBJECTS_H
