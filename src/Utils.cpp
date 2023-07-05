/*
 * Utils.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#include "Utils.h"
#include <iostream>

namespace gl3d::utils {

void printGLErrors() {
	for (auto x = glGetError(); x != GL_NO_ERROR; x = glGetError())
		std::cout << "Error: " << x << std::endl;
}

void GLAPIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar *message,
		const void *userParam) {
	std::cerr << "GL-DEBUG: ";
	if (type == GL_DEBUG_TYPE_ERROR)
		std::cerr << "Error: ";
	std::cerr << "[type=" << type << ", severity=" << severity << "] "
			<< message << std::endl;
}

void setupGLDebugging() {
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLDebugCallback, 0);
}

}  // namespace gl3d::utils
