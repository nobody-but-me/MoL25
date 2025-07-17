
#include <iostream>
#include <string>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <MOL/Application/core.hpp>

namespace Core {
    
    namespace WindowManager {
	int destroy_window(WINDOW *win) {
	    glfwDestroyWindow(win->buffer);
	    glfwTerminate();
	    
	    std::cout << "[INFO]: Window had been destroyed successfully." << std::endl;
	    return 0;
	}
	GLFWwindow *create_window(unsigned int w, unsigned int h, std::string title) {
	    GLFWwindow *window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
	    if (!window) {
		std::cout << "[FAILED]: Could not open OpenGL window" << std::endl;
		return nullptr;
	    }
	    glfwMakeContextCurrent(window);
	    int glad_version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	    if (!glad_version) {
		std::cout << "[FAILED]: Could not initialize OpenGL context. Engine is not glad." << std::endl;
		return nullptr;
	    }
	    std::cout << "[INFO]: Supported OpenGL version: " << glGetString(GL_VERSION) << "." << std::endl;
	    std::cout << "[INFO]: Renderer: " << glGetString(GL_RENDERER) << "." << std::endl;
	    return window;
	}
    }
    
    // --------------------------------------------------
    
    Engine::Engine() {
	if (!glfwInit()) {
	    std::cout << "[FAILED]: OpenGL library could not be loaded. \n" << std::endl;
	    glfwTerminate();
	    return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window.buffer = WindowManager::create_window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE);
	if (window.buffer == nullptr) return;
	
	std::cout << "\n--------------------------------------------------\n" << std::endl;
	std::cout << "[INFO]: Engine initialized succesfully" << std::endl;
	
	// main application loop. Perhaps it would be better to put this logic in another place;
	while (!glfwWindowShouldClose(window.buffer)) {
	    glfwPollEvents();
	    glClearColor(0.024f, 0.024f, 0.024f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    
	    // TODO: good implementation of delta time, but the "spiral of death" is possible.
	    previous_time = current_time;
	    current_time = glfwGetTime();
	    double frame_time = current_time - previous_time;
	    while (frame_time > 0.0f) {
		float dt = std::min(frame_time, delta);
		// --------------------------------------------------
		update(dt);
		// --------------------------------------------------
		frame_time -= dt;
		updates += dt;
	    }
	    
	    glfwSwapBuffers(window.buffer);
	}
	return;
    }
    
    void Engine::update(double delta_time) {
	return;
    }
    void Engine::render() {
	return;
    }
    void Engine::ready() {
	return;
    }
    
    Engine::~Engine() {
	WindowManager::destroy_window(&window);
	return;
    }
}

