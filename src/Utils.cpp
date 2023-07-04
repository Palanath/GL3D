/*
 * Utils.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#include "Utils.h"

namespace gl3d::utils {

void printGLErrors() {
	for (auto x = glGetError(); x != GL_NO_ERROR; x = glGetError())
		std::cout << "Error: " << x << std::endl;
}

}  // namespace gl3d::utils
