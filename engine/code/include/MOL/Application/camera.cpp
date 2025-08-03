
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <MOL/Application/camera.hpp>
#include <MOL/Application/core.hpp>
#include <molson.h>

namespace Core
{
    namespace Camera
    {
	// TODO: Refactor this whole code.
	const glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 1.0f);
	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 50.0f);
	
	static void update(glm::mat4 v, Shader *shader) {
	    v = glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(position.x, position.y, position.y) + FRONT, UP);
	    molson(set_matrix4)("view", &v, true, shader);
	}
	// Pretty simple implementation of camera position manipulator;
	void move(GLFWwindow *w, glm::mat4 view, Shader *shader) {
	    if (!Core::InputManager::is_key_pressed(w, GLFW_KEY_LEFT_SHIFT)) {
		// -- TODO: Hard-coded.
		// General movement: up, down, left right.
		if (Core::InputManager::is_key_pressed(w, GLFW_KEY_W))      { position.y += 0.2f * position.z/50.0f; update(view, shader); }
		else if (Core::InputManager::is_key_pressed(w, GLFW_KEY_S)) { position.y -= 0.2f * position.z/50.0f; update(view, shader); }
		if (Core::InputManager::is_key_pressed(w, GLFW_KEY_A))      { position.x -= 0.2f * position.z/50.0f; update(view, shader); }
		else if (Core::InputManager::is_key_pressed(w, GLFW_KEY_D)) { position.x += 0.2f * position.z/50.0f; update(view, shader); }
		// --
	    } else {
	    // Z movement: foward and backward.
		if (Core::InputManager::is_key_pressed(w, GLFW_KEY_W))      { position.z -= 0.3f; update(view, shader); }
		if (Core::InputManager::is_key_pressed(w, GLFW_KEY_S))      { position.z += 0.3f; update(view, shader); }
	    }
	}
    }
}
