/*
 * GPUModelGroup.h
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#ifndef MODELGROUP_H_
#define MODELGROUP_H_

#include "Model.h"

namespace gl3d {

class ModelGroup {
	friend class Model;
	GLuint vao, vertShader, fragShader, shader;
public:
	ModelGroup(const char *vertexShaderSource,
			const char *fragmentShaderSource);
	virtual ~ModelGroup();
	GLuint getUniformLoc(const char*);
	template<typename T>
	void setUniform(const char *uniformName, const T &value);
	template<typename T, int len>
	void setUniform(const char *uniformName, T value[len]);
	/*
	 * Calls relevant OpenGL functions to prepare for rendering one of the Models belonging to this group.
	 *
	 * This member function binds the vertex array associated with this ModelGroup and Uses the shader program associated with this group as well.
	 */
	void bind();
};

} /* namespace gl3d */

#endif /* MODELGROUP_H_ */
