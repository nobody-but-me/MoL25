
#ifndef CORE_H
#define CORE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>
#include <string>

#include <MOL/Utils/singleton.hpp>

enum KEYCODES {
    
    MOL_A = GLFW_KEY_A,
    MOL_B = GLFW_KEY_B,
    MOL_C = GLFW_KEY_C,
    MOL_D = GLFW_KEY_D,
    MOL_E = GLFW_KEY_E,
    MOL_F = GLFW_KEY_F,
    MOL_G = GLFW_KEY_G,
    MOL_H = GLFW_KEY_H,
    MOL_I = GLFW_KEY_I,
    MOL_J = GLFW_KEY_J,
    MOL_K = GLFW_KEY_K,
    MOL_L = GLFW_KEY_L,
    MOL_M = GLFW_KEY_M,
    MOL_N = GLFW_KEY_N,
    MOL_O = GLFW_KEY_O,
    MOL_P = GLFW_KEY_P,
    MOL_Q = GLFW_KEY_Q,
    MOL_R = GLFW_KEY_R,
    MOL_S = GLFW_KEY_S,
    MOL_T = GLFW_KEY_T,
    MOL_U = GLFW_KEY_U,
    MOL_V = GLFW_KEY_V,
    MOL_W = GLFW_KEY_W,
    MOL_X = GLFW_KEY_X,
    MOL_Y = GLFW_KEY_Y,
    MOL_Z = GLFW_KEY_Z,
    
    MOL_RCONTROL = GLFW_KEY_RIGHT_CONTROL,
    MOL_LCONTROL = GLFW_KEY_LEFT_CONTROL,
    MOL_RSHIFT   = GLFW_KEY_RIGHT_SHIFT,
    MOL_LSHIFT   = GLFW_KEY_LEFT_SHIFT,
    
    MOL_SPACE  = GLFW_KEY_SPACE,
    MOL_ENTER  = GLFW_KEY_ENTER,
    MOL_ESC = GLFW_KEY_ESCAPE,
    
    MOL_RIGHT = GLFW_KEY_RIGHT,
    MOL_LEFT  = GLFW_KEY_LEFT,
    MOL_DOWN  = GLFW_KEY_DOWN,
    MOL_UP    = GLFW_KEY_UP
    
};

namespace Core
{
    namespace WindowManager
    {
	typedef struct {
	    unsigned int IDEAL_HEIGHT;
	    unsigned int IDEAL_WIDTH;
	    unsigned int height;
	    unsigned int width;
	    std::string title;
	    
	    GLFWwindow *buffer; // the actual opengl window;
	} WINDOW;
	
	WINDOW create_window(unsigned int w, unsigned int h, std::string title);
	int destroy_window(WINDOW *win);
	
	void update_viewport_background(WindowManager::WINDOW *win);
    }
    
    namespace InputManager
    {
	// Extremely simple input handler.
	bool is_key_pressed(GLFWwindow *win_buffer, int key);
    }
    
    namespace Application
    {
	// Main engine class.
	class Engine: public Utils::Singleton<Engine>
	{
	    private:
		const std::string  DEFAULT_WINDOW_TITLE  = "MoL Game Engine";
		const unsigned int DEFAULT_WINDOW_WIDTH  = 1024;
		const unsigned int DEFAULT_WINDOW_HEIGHT = DEFAULT_WINDOW_WIDTH/16*9;
		WindowManager::WINDOW window;
		
		double previous_time = 0.0f;
		double current_time = 0.0f;
		double delta = 1 /60.0f;
		double updates = 0.0f;
		double time = 0.0f;
		
		glm::mat4 projection;
		glm::mat4 view;
		
	    public:
		// -- Getters.
		glm::mat4 get_projection() { return projection; }
		glm::mat4 get_view() { return view; }
		// --
		
		int init();
		
		void loop(double delta_time);
		void render();
		void ready();
		
		int destroy();
	    };
    }
}


#endif//CORE_H
