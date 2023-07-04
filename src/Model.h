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
	friend class ModelGroup;
	GLuint vbo;
	class ModelGroup* owner;
	int verts;
public:
	Model(ModelGroup*, float[], int);
	void render();
	void draw();
	virtual ~Model();
};

} /* namespace gl3d */

#endif /* MODEL_H_ */
