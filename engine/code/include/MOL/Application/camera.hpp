
#pragma once
#ifndef CAMERA_H
#define CAMERA_H


#include <glm/mat4x4.hpp>
#include <molson.h>

namespace Core
{
    // Is it really the better way to do this?
    namespace Camera
    {
	void move(GLFWwindow *w, glm::mat4 view, Shader *shader);
    }
}

#endif//CAMERA_H
