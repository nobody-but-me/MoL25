
#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <MOL/Gfx/object.hpp>
#include <molson.h>

namespace Gfx
{
    
    namespace Renderer // TODO: Perhaps that's not the best approach. Perhaps a renderer class would be more correct.
    {
	
	int init_rect_atom(Atom *rect_object, std::string rect_name);
	
	int init_atom_vertexes(Atom *object, unsigned int vertex_amount);
	int set_atom_transform(Atom *object, Shader *shader);
	void render_atom(Atom *object, Shader *shader);
	
    }
    
}

#endif//RENDERER_H
