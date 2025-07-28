
#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <MOL/Application/core.hpp>
#include <MOL/Gfx/renderer.hpp>

#define SHADER_PATH "../../engine/src/shaders/"

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
		std::cerr << "[FAILED]: Could not open OpenGL window." << std::endl;
		window.buffer = nullptr;
		return window;
	    }
	    glfwMakeContextCurrent(window.buffer);
	    int glad_version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	    if (!glad_version) {
		std::cerr << "[FAILED]: Could not initialize OpenGL context. Engine is not glad." << std::endl;
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
	    std::cerr << "[FAILED]: OpenGL library could not be loaded. \n" << std::endl;
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	
	ready();
	// main application loop. Perhaps it would be better to put this logic in another place;
	while (!glfwWindowShouldClose(window.buffer)) {
	    glfwPollEvents();
	    glClearColor(252.0f / 255.0f, 247.0f / 255.0f, 239.0f / 255.0f, 1.0f);
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
    
    // --------------------------------------------------
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view       = glm::mat4(1.0f);
    Shader object_default_shader;
    Atom rect;
    // --------------------------------------------------
    void Engine::ready() {
	std::cout << "[INFO]: Hello, MoL!" << std::endl;
	// -- TODO: re-place this logic.
	molson(init_shader)(SHADER_PATH"object_default.vert", SHADER_PATH"object_default.frag", &object_default_shader);
	
	projection = glm::perspective(glm::radians(45.0f), (float)window.width / (float)window.height, 0.1f, 100.0f);
	view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -50.0f));
	
	if (molson(set_matrix4)("projection", &projection, true, &object_default_shader) != 0) {
	    std::cerr << "[FAILED]: Projection failed." << std::endl;
	    return;
	}
	if (molson(set_matrix4)("view", &view, true, &object_default_shader) != 0) {
	    std::cerr << "[FAILED]: Projection failed." << std::endl;
	    return;
	}
	// -- 
	
	Gfx::Renderer::init_rect_atom(&rect, "Rectangle");
	Gfx::Renderer::init_atom_vertexes(&rect, 4);
	
	// 192, 223, 111
	rect.colour = glm::vec4(192.0f, 223.0f, 111.0f, 255.0f);
	rect.position = glm::vec3(0.0f, 0.0f, 0.0f);
	rect.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	rect.scale = glm::vec2(2.0f, 2.0f);
	return;
    }
    void Engine::loop(double delta_time) {
	return;
    }
    void Engine::render() {
	Gfx::Renderer::set_atom_transform(&rect, &object_default_shader);
	Gfx::Renderer::render_atom(&rect, &object_default_shader);
	return;
    }
    
    int Engine::destroy() {
	molson(destroy)(&object_default_shader);
	WindowManager::destroy_window(&window);
	return 0;
    }
}

