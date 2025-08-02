
#ifndef CORE_H
#define CORE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>
#include <string>

#include <MOL/Utils/singleton.hpp>

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
		const unsigned int DEFAULT_WINDOW_WIDTH  = 640;
		const unsigned int DEFAULT_WINDOW_HEIGHT = DEFAULT_WINDOW_WIDTH/4*3;
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
