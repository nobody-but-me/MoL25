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
	
	int init_cube_atom(Atom *cube_object, Material *material, std::string name) {
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
	    
	    if (material != NULL) {
		if (material->specular_map_path != "") material->specular_map = molson(load_texture)(material->specular_map_path.c_str(), material->specular_map_alpha);
		if (material->texture_path != "") material->texture = molson(load_texture)(material->texture_path.c_str(), material->alpha);
		cube_object->material = *material;
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
	
	int init_rect_atom(Atom *rect_object, Material *material, std::string name) {
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
	    
	    if (material != NULL) {
		if (material->specular_map_path != "") material->specular_map = molson(load_texture)(material->specular_map_path.c_str(), material->specular_map_alpha);
		if (material->texture_path != "") material->texture = molson(load_texture)(material->texture_path.c_str(), material->alpha);
		rect_object->material = *material;
	    }
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
	    return 0;
	}
	void render_atom(Atom *object, Shader *shader) {
	    molson(use_shader)(shader);
	    
	    // NOTE: that's so ugly!
	    if (object->light_vao == NULL) {
		if (object->material.texture_path == "") {
		    molson(set_bool)("is_textured", false, shader);
		    float spec[3], diff[3], ambt[3];
		    
		    if (object->material.specular == glm::vec3(0) || object->material.ambient == glm::vec3(0) || object->material.diffuse == glm::vec3(0)) {
			ambt[0] = object->colour.x / 255; ambt[1] = object->colour.y / 255; ambt[2] = object->colour.z / 255;
			diff[0] = object->colour.x / 255; diff[1] = object->colour.y / 255; diff[2] = object->colour.z / 255;
			spec[0] = 0.5f; spec[1] = 0.5f; spec[2] = 0.5f;
		    } else {
			// NOTE : don't know if that's the right way to do that.
			spec[0] = object->colour.x / 255 * object->material.specular.x;
			spec[1] = object->colour.y / 255 * object->material.specular.y;
			spec[2] = object->colour.z / 255 * object->material.specular.z;
			
			diff[0] = object->colour.x / 255 * object->material.diffuse.x;
			diff[1] = object->colour.y / 255 * object->material.diffuse.y;
			diff[2] = object->colour.z / 255 * object->material.diffuse.z;
			
			ambt[0] = object->colour.x / 255 * object->material.ambient.x;
			ambt[1] = object->colour.y / 255 * object->material.ambient.y;
			ambt[2] = object->colour.z / 255 * object->material.ambient.z;
		    }
		    
		    molson(set_float)("solid_material.shine", object->material.shininess, true, shader);
		    molson(set_vector3_f)("solid_material.specular", spec, true, shader);
		    molson(set_vector3_f)("solid_material.ambient", ambt, true, shader);
		    molson(set_vector3_f)("solid_material.diffuse", diff, true, shader);
		    
		} else {
		    molson(set_bool)("is_textured", true, shader);
		    
		    molson(set_int)("texture_material.diffuse", 0, true, shader);
		    glActiveTexture(GL_TEXTURE0);
		    glBindTexture(GL_TEXTURE_2D, object->material.texture.id);
		    
		    if (object->material.specular_map_path != "") {
			molson(set_int)("texture_material.specular", 1, true, shader);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, object->material.specular_map.id);
		    }
		    
		    float spec[3];
		    if (object->material.specular == glm::vec3(0)) {
			spec[0] = 5.0f;
			spec[1] = 5.0f;
			spec[2] = 5.0f;
		    } else {
			spec[0] = object->material.specular.x;
			spec[1] = object->material.specular.y;
			spec[2] = object->material.specular.z;
		    }
		    
		    molson(set_float)("texture_material.shine", object->material.shininess, true, shader);
		    molson(set_vector3_f)("texture_material.specular", spec, true, shader);
		}
	    }
	    if (object->light_vao == NULL) glBindVertexArray(object->vao);
	    else glBindVertexArray(object->light_vao);
	    glDrawArrays(GL_TRIANGLES, 0, object->indices);
	    glBindVertexArray(0);
	    return;
	}
	
    }
    
}
