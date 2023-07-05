#include "ModelGroup.h"

/*
 * ModelGroup.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#include <type_traits>
#include <iostream>
#include "Utils.h"

namespace gl3d {

ModelGroup::ModelGroup(const char *vertexShaderSource,
		const char *fragmentShaderSource) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
	glVertexAttribFormat(1, 3, GL_FLOAT, false, 0);
	glVertexAttribFormat(2, 3, GL_FLOAT, false, 0);
	glVertexAttribBinding(0, 0);
	glVertexAttribBinding(1, 1);
	glVertexAttribBinding(2, 2);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *src[1] = { vertexShaderSource };
	glShaderSource(vertShader, 1, src, nullptr);
	src[0] = fragmentShaderSource;
	glShaderSource(fragShader, 1, src, nullptr);
	glCompileShader(vertShader);
	glCompileShader(fragShader);

	shader = glCreateProgram();
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
}

/*
 * Returns the location of the uniform with the provided name.
 * To assign to the uniform, first ModelGroup::bind() should be invoked so that the associated program object is bound.
 */
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
	} else if constexpr (std::is_same_v<T, float>)
		if constexpr (len == 1)
			glUniform1f(getUniformLoc(uniformName), value[0]);
		else if constexpr (len == 2)
			glUniform2f(getUniformLoc(uniformName), value[0], value[1]);
		else if constexpr (len == 3)
			glUniform3f(getUniformLoc(uniformName), value[0], value[1],
					value[2]);

}

ModelGroup::~ModelGroup() {
	glDeleteVertexArrays(1, &vao);
	glDetachShader(shader, vertShader);
	glDeleteShader(vertShader);
	glDetachShader(shader, fragShader);
	glDeleteShader(fragShader);
	glDeleteProgram(shader);
}

/*
 * Binds the associated VAO and uses the associated program. This should be called when e.g. setting uniform values or before rendering.
 */
void ModelGroup::bind() {
	glBindVertexArray(vao);
	glUseProgram(shader);
}

} /* namespace gl3d */
