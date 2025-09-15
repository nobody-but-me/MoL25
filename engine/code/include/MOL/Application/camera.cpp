
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <MOL/Application/camera.hpp>
#include <MOL/Application/core.hpp>
#include <molson.h>

constexpr int FREE_MOUSE_MODE = 0;
constexpr int VIEW_MODE = 1;

constexpr float SENSITIVITY = 0.1f;

namespace Core
{
    namespace Camera
    {
	
	const float SPEED = 15.0;
	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 50.0f);
	glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float last_x = 800.0f / 2.0;
	float last_y = 600.0 / 2.0;
	float pitch =  0.0f;
	float yaw = -90.0f;
	
	float rotation = 0.0f;
	
	bool first_mouse = false;
	
	Shader *m_lighting_shader;
	GLFWwindow *m_window;
	glm::mat4 m_view;
	Shader *m_shader;
	
	int current_mode = VIEW_MODE;
	
	float get_sensitivity()  { return SENSITIVITY; }
	float get_rotation()     { return rotation; }
	const float get_speed()  { return SPEED; }
	
	glm::vec3 get_position() { return position; }
	glm::vec3 get_front()    { return FRONT; }
	glm::vec3 get_up()       { return UP; }
	
	void update(glm::mat4 v, Shader *shader) {
	    v = glm::lookAt(position, position + FRONT, UP);
	    molson(set_matrix4)("view", &v, true, shader);
	}
	
	static void mouse_callback(GLFWwindow* w, double x_position, double y_position) {
	    if (current_mode == VIEW_MODE) {
		float pos_x = static_cast<float>(x_position);
		float pos_y = static_cast<float>(y_position);

		if (first_mouse) {
		    first_mouse = false;
		    last_x = pos_x;
		    last_y = pos_y;
		}
		
		float offset_x = pos_x - last_x;
		float offset_y = last_y - pos_y;
		last_x = pos_x;
		last_y = pos_y;
		
		offset_x *= SENSITIVITY;
		offset_y *= SENSITIVITY;
		
		pitch += offset_y;
		yaw += offset_x;
		
		if (pitch < -89.0f) pitch = -89.0f;
		if (pitch > 89.0f) pitch = 89.0f;
		
		glm::vec3 f;
		f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		f.y = sin(glm::radians(pitch));
		f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		FRONT = glm::normalize(f);
	    }
	    return;
	}
	
	void init(GLFWwindow *w, int window_width, glm::mat4 view, Shader *shader, Shader *lighting_shader) {
	    update(view, lighting_shader);
	    update(view, shader);
	    
	    m_lighting_shader = lighting_shader;
	    m_shader = shader;
	    m_view = view;
	    m_window = w;
	    
	    last_y = (window_width/4*3)/2;
	    last_x = window_width/2;
	    
	    glfwSetCursorPosCallback(w, mouse_callback);
	}
	
	void move(double delta) {
	    
	    if (current_mode == VIEW_MODE) {
		float camera_speed = static_cast<float>(SPEED * delta);
		
		if (Core::InputManager::is_key_pressed(m_window, MOL_W)) position += camera_speed * FRONT;
		if (Core::InputManager::is_key_pressed(m_window, MOL_S)) position -= camera_speed * FRONT;
		if (Core::InputManager::is_key_pressed(m_window, MOL_A)) position -= glm::normalize(glm::cross(FRONT, UP)) * camera_speed;
		if (Core::InputManager::is_key_pressed(m_window, MOL_D)) position += glm::normalize(glm::cross(FRONT, UP)) * camera_speed;
		
		if (Core::InputManager::is_key_pressed(m_window, MOL_LSHIFT)) position.y -= camera_speed;
		if (Core::InputManager::is_key_pressed(m_window, MOL_SPACE)) position.y += camera_speed;
		
		if (m_shader != NULL && m_lighting_shader != NULL) {
		    update(m_view, m_lighting_shader);
		    update(m_view, m_shader);
		}
		
		if (Core::InputManager::is_key_pressed(m_window, MOL_ESC)) {
		    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		    current_mode = FREE_MOUSE_MODE;
		}
	    }
	    else if (current_mode == FREE_MOUSE_MODE) {
		if (Core::InputManager::is_key_pressed(m_window, MOL_V)) {
		    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		    current_mode = VIEW_MODE;
		}
	    }
	}
    }
}
