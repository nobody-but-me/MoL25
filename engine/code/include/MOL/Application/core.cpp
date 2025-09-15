
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <MOL/Application/camera.hpp>
#include <MOL/Application/core.hpp>
#include <MOL/Gfx/renderer.hpp>

#define SHADER_PATH "../../engine/code/shaders/"
#define ASSETS_PATH "../../engine/assets/"

namespace Core
{
    
    namespace WindowManager
    {
	int destroy_window(WindowManager::WINDOW *win) {
	    glfwDestroyWindow(win->buffer);
	    glfwTerminate();
	    
	    std::cout << "\n--------------------------------------------------\n" << std::endl;
	    std::cout << "[INFO]: Window had been destroyed successfully." << std::endl;
	    return 0;
	}
	
	// Window resize callback. Resize and re-place the viewport as the window is resized. It would be interesting in the future to let the developer choose if it wants the viewport to expand with the window or not.
	static void window_buffer_size_callback(GLFWwindow *win, int w, int h) {
	    glfwGetFramebufferSize(win, &w, &h);
	    // TODO: hard-coded.
	    unsigned int width = 1024;
	    glViewport(w / 2 - (width / 2), h / 2 - (width/16*9 / 2), width, width/16*9);
	    return;
	}
	WindowManager::WINDOW create_window(unsigned int w, unsigned int h, std::string title) {
	    WindowManager::WINDOW window;;
	    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	    window.buffer = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
	    
	    // Makes sure window was initialized correctly.
	    if (!window.buffer) {
		std::cerr << "[FAILED]: Could not open OpenGL window." << std::endl;
		window.buffer = nullptr;
		return window;
	    }
	    // Setting values and making window buffer the current context.
	    glfwMakeContextCurrent(window.buffer);
	    window.IDEAL_HEIGHT = h;
	    window.IDEAL_WIDTH  = w;
	    window.height = h;
	    window.width  = w;
	    
	    // Initializing glad.
	    int glad_version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	    if (!glad_version) {
		std::cerr << "[FAILED]: Could not initialize OpenGL context. The engine is, for sure, not glad." << std::endl;
		window.buffer = nullptr;
		return window;
	    }
	    // Setting viewport size and position and setting window resize callback.
	    glViewport(window.IDEAL_WIDTH / 2 - (window.IDEAL_WIDTH / 2), window.IDEAL_HEIGHT / 2 - (window.IDEAL_HEIGHT / 2), window.IDEAL_WIDTH, window.IDEAL_HEIGHT);
	    glfwSetFramebufferSizeCallback(window.buffer, window_buffer_size_callback);
	    
	    // Defining OpenGL blending filters.
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_BLEND);
	    
	    std::cout << "[INFO]: Supported OpenGL version: " << glGetString(GL_VERSION) << "." << std::endl;
	    std::cout << "[INFO]: Renderer: " << glGetString(GL_RENDERER) << "." << std::endl;
	    return window;
	}
	
	void update_viewport_background(WindowManager::WINDOW *win) {
	    // Getting current window size.
	    int w, h;
	    glfwGetWindowSize(win->buffer, &w, &h);
	    // -- Setting viewport background colour creating a rectangle selection of the ideal with and height and cleaning it with a whitish colour.
	    glEnable(GL_SCISSOR_TEST);
	    glScissor(w / 2 - (win->IDEAL_WIDTH / 2), h / 2 - (win->IDEAL_HEIGHT / 2), win->IDEAL_WIDTH, win->IDEAL_HEIGHT);
	    glClearColor(24.0f / 255.0f, 24.0f / 255.0f, 24.0f / 255.0f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);
	    glDisable(GL_SCISSOR_TEST);
	    return;
	}
    }
    
    namespace InputManager
    {
	bool is_key_pressed(GLFWwindow *win_buffer, int key) {
	    int state = glfwGetKey(win_buffer, key);
	    if (state == GLFW_PRESS) {
		return true;
	    }
	    return false;
	}
    }
    
    // --------------------------------------------------
    namespace Application {
	
	int Engine::init() {
	    // GLFW initializing.
	    if (!glfwInit()) {
		std::cerr << "[FAILED]: OpenGL library could not be loaded. \n" << std::endl;
		glfwTerminate();
		return 1;
	    }
	    // Simple glfw configuration setting.
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    
	    // -- Initializing main window.
	    window = WindowManager::create_window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE);
	    if (window.buffer == nullptr) return 1;
	    
	    std::cout << "\n--------------------------------------------------\n" << std::endl;
	    std::cout << "[INFO]: Engine initialized succesfully." << std::endl;
	    ready();
	    // main application loop. Perhaps it would be better to put this logic in another place.
	    while (!glfwWindowShouldClose(window.buffer)) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Closing window with escape key.
		if (InputManager::is_key_pressed(window.buffer, MOL_ESC)) {
		    break;
		}
		
		// -- Updating viewport background colour.
		WindowManager::update_viewport_background(&window);
		
		// TODO: fix possibility of the spiral of death.
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
	
	Shader object_default_shader;
	Shader light_default_shader;
	
	glm::vec3 light_pos(-0.2f, -20.0f, -25.0f);
	Atom cube, cube2, plane, light_cube;
	
	float light_specular_colour[3] = { 1.0f, 1.0f, 1.0f };
	float light_ambient_colour[3]  = { 0.2f, 0.2f, 0.2f };
	float light_diffuse_colour[3]  = { 0.5f, 0.5f, 0.5f };
	
	// --------------------------------------------------
	void Engine::ready() {
	    std::cout << "[INFO]: Hello, MoL!" << std::endl;
	    
	    // -- TODO: re-place this whole logic to a better place. --
	    
	    projection = glm::mat4(1.0f);
	    view       = glm::mat4(1.0f);
	    
	    molson(init_shader)(SHADER_PATH"object_default.vert", SHADER_PATH"object_default.frag", &object_default_shader);
	    molson(init_shader)(SHADER_PATH"light_default.vert", SHADER_PATH"light_default.frag", &light_default_shader);
	    
	    projection = glm::perspective(glm::radians(45.0f), (float)window.width / (float)window.height, 0.1f, 350.0f);
	    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -50.0f));
	    
	    if (molson(set_matrix4)("projection", &projection, true, &object_default_shader) != 0) { std::cerr << "[FAILED]: Perspective projection setting failed." << std::endl; return; }
	    if (molson(set_matrix4)("view", &view, true, &object_default_shader) != 0) { std::cerr << "[FAILED]: View projection setting failed." << std::endl; return; }
	    
	    if (molson(set_matrix4)("projection", &projection, true, &light_default_shader) != 0) { std::cerr << "[FAILED]: Lighting perspective projection setting failed." << std::endl; return; }
	    if (molson(set_matrix4)("view", &view, true, &light_default_shader) != 0) { std::cerr << "[FAILED]: Lighting view projection setting failed." << std::endl; return; }
	    
	    Core::Camera::init(window.buffer, window.width, view, &object_default_shader, &light_default_shader);
	    // -- 
	    
	    // -- Materials initialization
	    
	    // Texture material configuration;
	    Material texture_material;
	    texture_material.specular_map_path = ASSETS_PATH"container2_specular.png";
	    texture_material.specular_map_alpha = true;
	    
	    texture_material.texture_path = ASSETS_PATH"container2.png";
	    texture_material.alpha = true;
	    
	    texture_material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	    texture_material.shininess = 32.0f;
	    
	    // Solid colour material configuration;
	    Material colour_material;
	    colour_material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	    colour_material.diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
	    colour_material.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	    colour_material.shininess = 8.0f;
	    
	    // Directional Light material configuration;
	    LightMaterial directional_light_material;
	    directional_light_material.object_shader = &object_default_shader;
	    
	    directional_light_material.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	    directional_light_material.specular  = glm::vec3(1.0f, 1.0f, 1.0f);
	    directional_light_material.diffuse   = glm::vec3(1.0f, 1.0f, 1.0f);
	    directional_light_material.ambient   = glm::vec3(0.2f, 0.2f, 0.2f);
	    
	    // Point Light material configuration;
	    LightMaterial point_light_material;
	    point_light_material.object_shader = &object_default_shader;
	    
	    point_light_material.quadratic = 0.0019f;
	    point_light_material.constant  =    1.0f;
	    point_light_material.linear    =  0.022f;
	    
	    point_light_material.specular  = glm::vec3(1.0f, 1.0f, 1.0f);
	    point_light_material.diffuse   = glm::vec3(1.0f, 1.0f, 1.0f);
	    point_light_material.ambient   = glm::vec3(0.2f, 0.2f, 0.2f);
	    
	    // SpotLight material configuration;
	    LightMaterial spotlight_material;
	    spotlight_material.object_shader = &object_default_shader;
	    
	    spotlight_material.direction = glm::vec3( 0.0f, -20.0f, 0.0f);
	    spotlight_material.radius    = 15.0f;
	    
	    spotlight_material.specular  = glm::vec3(0.5f, 0.5f, 0.5f);
	    spotlight_material.diffuse   = glm::vec3(1.0f, 1.0f, 1.0f);
	    spotlight_material.ambient   = glm::vec3(0.1f, 0.1f, 0.1f);
	    
	    // --
	    
	    // Initializing cube and cube2 objcets.
	    Gfx::Renderer::init_cube_atom(&cube, &texture_material, "Cube");
	    Gfx::Renderer::init_atom_vertexes(&cube, &object_default_shader);
	    
	    Gfx::Renderer::init_cube_atom(&cube2, &texture_material, "Cube");
	    Gfx::Renderer::init_atom_vertexes(&cube2, &object_default_shader);
	    
	    cube.colour   = glm::vec4(255.0f, 255.0f, 0.0f, 255.0f);
	    cube.rotation = glm::vec3(0.0f, 25.0f, -25.0f);
	    cube.scale    = glm::vec3(8.0f, 8.0f, 8.0f);
	    cube.position = glm::vec3(0.0f, 0.0f, 0.0f);
	    
	    cube2.colour   = cube.colour; cube2.scale    = cube.scale;
	    cube2.rotation = glm::vec3(45.0f, 0.0f,  25.0f);
	    cube2.position = glm::vec3(0.0f, 0.0f, -150.0f);
	    
	    // Initializing plane object.
	    Gfx::Renderer::init_rect_atom(&plane, &colour_material, "Plane");
	    Gfx::Renderer::init_atom_vertexes(&plane, &object_default_shader);
	    
	    plane.colour   = glm::vec4(100.0f, 80.0f, 80.0f, 255.0f);
	    plane.position = glm::vec3(-25.0f, -25.0f, -25.0f);
	    plane.scale    = glm::vec3(50.0f, 50.0f, 50.0f);
	    plane.rotation = glm::vec3(90.0f, 0.0f, 0.0f);
	    
	    // Initializing point-type light cube.
	    Gfx::Renderer::init_light_atom(&light_cube, POINT_LIGHT, &point_light_material, "Light");
	    Gfx::Renderer::init_atom_vertexes(&light_cube, &light_default_shader);
	    
	    light_cube.position = glm::vec3( 0.0f, 0.0f, 0.0f);
	    light_cube.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	    light_cube.scale    = glm::vec3(5.0f, 5.0f, 5.0f);
	    
	    return;
	}
	
	void Engine::loop(double delta_time) {
	    // Moving light cube in a circle-way.
	    light_cube.position.x = std::cos((float)glfwGetTime() * 0.5f) * 15.0f;
	    light_cube.position.z = std::sin((float)glfwGetTime() * 0.5f) * 15.0f;
	    
	    // Updating view position shader uniform variable.
	    Core::Camera::move(delta_time);
	    glm::vec3 camera_position = Core::Camera::get_position();
	    float cp[3] = { camera_position.x, camera_position.y, camera_position.z };
	    molson(set_vector3_f)("view_position", cp, true, &object_default_shader);
	    return;
	}
	void Engine::render() {
	    // Rendering all the present objects.
	    Gfx::Renderer::set_atom_transform(&cube, &object_default_shader);
	    Gfx::Renderer::render_atom(&cube, &object_default_shader);
	    Gfx::Renderer::set_atom_transform(&cube2, &object_default_shader);
	    Gfx::Renderer::render_atom(&cube2, &object_default_shader);
	    
	    Gfx::Renderer::set_atom_transform(&plane, &object_default_shader);
	    Gfx::Renderer::render_atom(&plane, &object_default_shader);
	    
	    Gfx::Renderer::set_atom_transform(&light_cube, &light_default_shader);
	    Gfx::Renderer::render_atom(&light_cube, &light_default_shader);
	    return;
	}
	
	int Engine::destroy() {
	    // Destroying dependencies. The objects do not have to be destroyed since their destroyed is called automatically.
	    molson(destroy_shader)(&object_default_shader);
	    WindowManager::destroy_window(&window);
	    return 0;
	}
    }
}

