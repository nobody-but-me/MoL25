
#include <iostream>
#include <string>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <MOL/Application/core.hpp>

namespace Core
{
    
    namespace WindowManager
    {
	int destroy_window(WINDOW *win) {
	    glfwDestroyWindow(win->buffer);
	    glfwTerminate();
	    
	    std::cout << "\n--------------------------------------------------\n" << std::endl;
	    std::cout << "[INFO]: Window had been destroyed successfully." << std::endl;
	    return 0;
	}
	WindowManager::WINDOW create_window(unsigned int w, unsigned int h, std::string title) {
	    WindowManager::WINDOW window;
	    window.buffer = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
	    window.IDEAL_HEIGHT = h;
	    window.IDEAL_WIDTH  = w;
	    window.height = h;
	    window.width  = w;
	    
	    if (!window.buffer) {
		std::cout << "[FAILED]: Could not open OpenGL window." << std::endl;
		window.buffer = nullptr;
		return window;
	    }
	    glfwMakeContextCurrent(window.buffer);
	    int glad_version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	    if (!glad_version) {
		std::cout << "[FAILED]: Could not initialize OpenGL context. Engine is not glad." << std::endl;
		window.buffer = nullptr;
		return window;
	    }
	    
	    std::cout << "[INFO]: Supported OpenGL version: " << glGetString(GL_VERSION) << "." << std::endl;
	    std::cout << "[INFO]: Renderer: " << glGetString(GL_RENDERER) << "." << std::endl;
	    return window;
	}
    }
    
    // --------------------------------------------------
    
    int Engine::init() {
	if (!glfwInit()) {
	    std::cout << "[FAILED]: OpenGL library could not be loaded. \n" << std::endl;
	    glfwTerminate();
	    return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window.IDEAL_HEIGHT = DEFAULT_WINDOW_HEIGHT;
	window.IDEAL_WIDTH  = DEFAULT_WINDOW_WIDTH;
	
	window = WindowManager::create_window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE);
	if (window.buffer == nullptr) return 1;
	
	std::cout << "\n--------------------------------------------------\n" << std::endl;
	std::cout << "[INFO]: Engine initialized succesfully." << std::endl;
	
	ready();
	// main application loop. Perhaps it would be better to put this logic in another place;
	while (!glfwWindowShouldClose(window.buffer)) {
	    glfwPollEvents();
	    glClearColor(0.024f, 0.024f, 0.024f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    
	    // TODO: possibility of spiral of death.
	    previous_time = current_time;
	    current_time = glfwGetTime();
	    double frame_time = current_time - previous_time;
	    while (frame_time > 0.0f) {
		float dt = std::min(frame_time, delta);
		// --------------------------------------------------
		loop(dt);
		// --------------------------------------------------
		frame_time -= dt;
		updates += dt;
	    }
	    render();
	    glfwSwapBuffers(window.buffer);
	}
	destroy();
	return 0;
    }
    
    void Engine::loop(double delta_time) {
	return;
    }
    void Engine::render() {
	return;
    }
    void Engine::ready() {
	std::cout << "[INFO]: Hello, MoL!" << std::endl;
	return;
    }
    
    int Engine::destroy() {
	WindowManager::destroy_window(&window);
	return 0;
    }
}

