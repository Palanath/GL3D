/*
 * GPUModelGroup.h
 *
 *  Created on: Jul 4, 2023
 *      Author: Palanath
 */

#ifndef GPUMODELGROUP_H_
#define MODELGROUP_H_

#include "Model.h"


namespace gl3d {

class ModelGroup {
	GLuint vao, vertShader, fragShader, shader;
public:
	ModelGroup(const char* vertexShaderSource, const char* fragmentShaderSource);
	virtual ~ModelGroup();
	GLuint getUniformLoc(const char*);
	template<typename T>
	void setUniform(const char *uniformName, const T &value);
	template<typename T, int len>
	void setUniform(const char *uniformName, T value[len]);
	class Model* createModel(float data[], int length);
};

} /* namespace gl3d */

#endif /* GPUMODELGROUP_H_ */
