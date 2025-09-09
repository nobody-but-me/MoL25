// Example of my goal with the MOL rendering pipeline.
//    I want something modular, a rendering process that gives the developer the 
//    ability to choose more freely what it wants, with abstractions but not to 
//    the point of calling only two single functions to build an object.
//
// Atom rectangle;
// Gfx::Renderer::init_rect_geometry(&rectangle);
// Gfx::Renrerer::init_atom_vertexes(&rectangle, 4);
// ...
// Gfx::Renderer::set_atom_transform(&rectangle);
// Gfx::Renderer::render_atom(&rectangle);

// #include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include <MOL/Gfx/object.hpp>
#define MOLSON_IMPLEMENTATION
#include <molson.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

namespace Gfx
{
    
    namespace Renderer
    {
	static int check4opengl_errors() {
	    GLenum err = glGetError();
	    if ((err == glGetError()) != GL_NO_ERROR) {
		if (err == GL_NO_ERROR) return 0;
		std::string error_message;
		// tee-hee.
		if (err == GL_INVALID_ENUM) error_message                       = "Invalid enum.";
		else if (err == GL_INVALID_VALUE) error_message                 = "Invalid value.";
		else if (err == GL_INVALID_OPERATION) error_message             = "Invalid operation.";
		else if (err == GL_STACK_OVERFLOW) error_message                = "stack overflow.";
		else if (err == GL_STACK_UNDERFLOW) error_message               = "stack underflow.";
		else if (err == GL_OUT_OF_MEMORY) error_message                 = "out of memory.";
		else if (err == GL_INVALID_FRAMEBUFFER_OPERATION) error_message = "Invalid framebuffer operation.";
		
		std::cerr << "[FAILED]: OpenGL error :: " << error_message << std::endl;
		return 1;
	    }
	    return 0;
	}
	
	int init_cube_atom(Atom *cube_object, std::string texture_path, bool alpha, std::string name) {
	    cube_object->name = name;
	    float vertices[] = {
		
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f, 0.0f
		
	    };
	    glGenVertexArrays(1, &cube_object->vao);
	    glBindVertexArray(cube_object->vao);
	    glGenBuffers(1, &cube_object->vbo);
	    
	    glBindBuffer(GL_ARRAY_BUFFER, cube_object->vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	    cube_object->indices = 36;
	    
	    cube_object->alpha = alpha;
	    if (texture_path != "") {
		cube_object->texture = molson(load_texture)(texture_path.c_str(), alpha);
		cube_object->texture_path = texture_path;
	    }
	    return check4opengl_errors();
	}
	int init_light_atom(Atom *light_object, std::string name) {
	    light_object->name = name;
	    float vertices[] = {
		
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
		
	    };
	    glGenVertexArrays(1, &light_object->light_vao);
	    glBindVertexArray(light_object->light_vao);
	    glGenBuffers(1, &light_object->vbo);
	    
	    glBindBuffer(GL_ARRAY_BUFFER, light_object->vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	    light_object->indices = 36;
	    
	    return check4opengl_errors();
	}
	
	// --------------------------------------------------
	
	int init_sprite_atom(Atom *sprite_object, std::string texture_path, bool alpha, std::string name) {
	    sprite_object->name = name;
	    float vertices[] = {
		0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		
		0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f
	    };
	    glGenVertexArrays(1, &sprite_object->vao);
	    glBindVertexArray(sprite_object->vao);
	    glGenBuffers(1, &sprite_object->vbo);
	    
	    glBindBuffer(GL_ARRAY_BUFFER, sprite_object->vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	    sprite_object->indices = 6;
	    
	    sprite_object->alpha = alpha;
	    if (texture_path != "") {
		sprite_object->texture = molson(load_texture)(texture_path.c_str(), alpha);
		sprite_object->texture_path = texture_path;
	    }
	    return check4opengl_errors();
	}
	int init_rect_atom(Atom *rect_object, std::string name) {
	    rect_object->name = name;
	    float vertices[] = {
		0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		
		0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f
	    };
	    glGenVertexArrays(1, &rect_object->vao);
	    glBindVertexArray(rect_object->vao);
	    glGenBuffers(1, &rect_object->vbo);
	    
	    glBindBuffer(GL_ARRAY_BUFFER, rect_object->vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	    rect_object->indices = 6;
	    
	    return check4opengl_errors();
	}
	int init_atom_vertexes(Atom *object, Shader *shader) {
	    if (object->light_vao == NULL) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	    } else {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	    }
	    
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	    glBindVertexArray(0);
	    
	    return check4opengl_errors();
	}
	int set_atom_transform(Atom *object, Shader *shader) {
	    molson(use_shader)(shader);
	    glm::mat4 trans = glm::mat4(1.0f);
	    trans = glm::translate(trans, glm::vec3(object->position));
	    
	    trans = glm::translate(trans, glm::vec3(0.5f * object->scale.x, 0.5f * object->scale.y, 0.5f * object->scale.z ));
	    trans = glm::rotate(trans, glm::radians(object->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	    trans = glm::rotate(trans, glm::radians(object->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	    trans = glm::rotate(trans, glm::radians(object->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	    trans = glm::translate(trans, glm::vec3(-0.5f * object->scale.x, -0.5f * object->scale.y, -0.5f * object->scale.z ));
	    
	    trans = glm::scale(trans, glm::vec3(object->scale));
	    
	    if (molson(set_matrix4)("transform", &trans, false, shader) != 0) {
		std::cerr << "[FAILED]: Object transform could not be set." << std::endl;
		return 1;
	    }
	    
	    if (object->light_vao == NULL) {
		float c[3];
		c[0] = object->colour[0] / 255;
		c[1] = object->colour[1] / 255;
		c[2] = object->colour[2] / 255;
		
		float l[3];
		l[0] = 1.0f;
		l[1] = 1.0f;
		l[2] = 1.0f;
		
		if (molson(set_vector3_f)("light_colour", l, true, shader) != 0) {
		    std::cerr << "[FAILED]: Object colour could not be set." << std::endl;
		    return 1;
		}
		if (molson(set_vector3_f)("colour", c, true, shader) != 0) {
		    std::cerr << "[FAILED]: Object colour could not be set." << std::endl;
		    return 1;
		}
	    }
	    if (object->texture_path != "") molson(set_bool)("is_textured", true, shader);
	    return 0;
	}
	void render_atom(Atom *object, Shader *shader) {
	    molson(use_shader)(shader);
	    
	    if (object->texture_path != "") {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->texture.id);
		molson(set_bool)("is_textured", true, shader);
	    } else {
		molson(set_bool)("is_textured", false, shader);
	    }
	    
	    if (object->light_vao == NULL) glBindVertexArray(object->vao);
	    else glBindVertexArray(object->light_vao);
	    glDrawArrays(GL_TRIANGLES, 0, object->indices);
	    glBindVertexArray(0);
	    return;
	}
	
    }
    
}
