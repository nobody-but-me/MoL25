
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
    
    bool initialized;
    std::string name;
    
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
