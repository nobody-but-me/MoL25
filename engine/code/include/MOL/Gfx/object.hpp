
#ifndef OBJECTS_H
#define OBJECTS_H

#include <molson.h>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

typedef struct
{
    
    std::string texture_path = "";
    Texture texture;
    bool alpha;
    
    std::string specular_map_path = "";
    bool specular_map_alpha;
    Texture specular_map;
    
    float shininess = 32.0f;
    bool material = false;
    
    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    
} Material;

typedef struct
{
    
    bool initialized;
    std::string name;
    
    Material material;
    
    unsigned int light_vao;
    unsigned int indices;
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    
    glm::mat4 transform;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    glm::vec4 colour;
} Atom;

#endif//OBJECTS_H
