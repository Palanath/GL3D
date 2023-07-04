/*
 * Model.h
 *
 *  Created on: Jul 3, 2023
 *      Author: Palanath
 */

#ifndef MODEL_H_
#define MODEL_H_

namespace gl3d {

class Model {
	GLuint vbo;

public:
	Model(float*, int);
	virtual ~Model();
};

} /* namespace gl3d */

#endif /* GPUMODEL_H_ */
