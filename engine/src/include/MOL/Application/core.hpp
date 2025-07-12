
#ifndef CORE_H
#define CORE_H

#include <GLFW/glfw3.h>
#include <string>

namespace Core {
    
    namespace WindowManager {
	
	typedef struct {
	    unsigned int height;
	    unsigned int width;
	    std::string title;
	    
	    GLFWwindow *buffer; // the actual opengl window;
	} WINDOW;
	
	int destroy_window(WINDOW &window);
	int create_window(WINDOW &window);
    }
    
    class Engine {
	private:
	    const std::string  DEFAULT_WINDOW_TITLE  = "MoL Game Engine";
	    const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
	    const unsigned int DEFAULT_WINDOW_WIDTH  = 800;
	    
	public:
	    Engine();
	    
	    void update(double delta_time);
	    void render();
	    void ready();
	    
	    ~Engine();
    };
}


#endif//CORE_H
