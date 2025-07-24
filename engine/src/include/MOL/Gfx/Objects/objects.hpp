
#ifndef OBJECTS_H
#define OBJECTS_H

#include <MOL/Utils/singleton.hpp>

namespace Objects
{
    
    typedef struct Object
    {
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
    };
    
}

#endif//OBJECTS_H
