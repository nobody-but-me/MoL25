
#ifndef CORE_H
#define CORE_H

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
    
    class Engine: public Utils::Singleton<Engine>
    {
	private:
	    const std::string  DEFAULT_WINDOW_TITLE  = "MoL Game Engine";
	    const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
	    const unsigned int DEFAULT_WINDOW_WIDTH  = 800;
	    WindowManager::WINDOW window;
	    
	    double previous_time = 0.0f;
	    double current_time = 0.0f;
	    double delta = 1 /60.0f;
	    double updates = 0.0f;
	    double time = 0.0f;
	    
	public:
	    int init();
	    
	    void loop(double delta_time);
	    void render();
	    void ready();
	    
	    int destroy();
    };
}


#endif//CORE_H
