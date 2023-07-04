#include "ModelGroup.h"

/*
 * ModelGroup.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#include <type_traits>

namespace gl3d {

ModelGroup::ModelGroup(const char *vertexShaderSource,
		const char *fragmentShaderSource) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 9, (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 9,
			(void*) (sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 9,
			(void*) (sizeof(float) * 3));
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

ModelGroup::~ModelGroup() {
	glDetachShader(shader, vertShader);
	glDeleteShader(vertShader);
	glDetachShader(shader, fragShader);
	glDeleteShader(fragShader);
	glDeleteProgram(shader);
}

class Model* ModelGroup::createModel(float data[], int length) {
	return new Model(this, data, length);
}

} /* namespace gl3d */
