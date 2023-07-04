#include "ModelGroup.h"

/*
 * GPUModelGroup.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#include <type_traits>

namespace gl3d {

GLuint ModelGroup::getUniformLoc(const char *name) {
	return glGetUniformLocation(shader, name);
}
template<typename T>
void ModelGroup::setUniform(const char *uniformName, const T &value) {
	if constexpr (std::is_same_v<T, int>)
		glUniform1i(getUniformLoc(uniformName), value);
	else if constexpr (std::is_same_v<T, float>)
		glUniform1f(getUniformLoc(uniformName), value);
}

template<typename T, int len>
void ModelGroup::setUniform(const char *uniformName, T value[len]) {
	if constexpr (std::is_same_v<T, int>) {
		if constexpr (len == 1)
			glUniform1i(getUniformLoc(uniformName), value[0]);
		else if constexpr (len == 2)
			glUniform2i(getUniformLoc(uniformName), value[0], value[1]);
		else if constexpr (len == 3)
			glUniform3i(getUniformLoc(uniformName), value[0], value[1],
					value[2]);
	} else if constexpr (std::is_same_v<T, float>) {
		if constexpr (len == 1)
			glUniform1f(getUniformLoc(uniformName), value[0]);
		else if constexpr (len == 2)
			glUniform2f(getUniformLoc(uniformName), value[0], value[1]);
		else if constexpr (len == 3)
			glUniform3f(getUniformLoc(uniformName), value[0], value[1],
					value[2]);
	}
}

ModelGroup::ModelGroup() {
	// TODO Auto-generated constructor stub

}

ModelGroup::~ModelGroup() {
	// TODO Auto-generated destructor stub
}

} /* namespace gl3d */
