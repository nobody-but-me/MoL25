
#pragma once
#ifndef CAMERA_H
#define CAMERA_H


#include <glm/mat4x4.hpp>
#include <molson.h>

namespace Core
{
    // Is it really the better way to do this?
    // no, daniel, it is not.
    namespace Camera
    {
	void init(GLFWwindow *w, int window_width, glm::mat4 view, Shader *shader, Shader *lighting_shader);
	void update(glm::mat4 v, Shader *shader);
	void move(double delta);
    }
}

#endif//CAMERA_H
