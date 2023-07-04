/*
 * Model.h
 *
 *  Created on: Jul 3, 2023
 *      Author: Palanath
 */

#ifndef MODEL_H_
#define MODEL_H_
#include "ModelGroup.h"

namespace gl3d {

class Model {
	GLuint vbo;
	class ModelGroup* owner;
public:
	Model(ModelGroup*, float[], int);
	virtual ~Model();
};

} /* namespace gl3d */

#endif /* MODEL_H_ */
