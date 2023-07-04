#include "Model.h"
#include "ModelGroup.h"


/*
 * Model.cpp
 *
 *  Created on: Jul 3, 2023
 *      Author: Palanath
 */

namespace gl3d {

// TODO Make ModelGroup-style class that contains a VAO and shader for rendering. Instances should have methods to create Models, each of which access the group's vao and shader.

/*
 * Creates a new GPUModel object with the provided data array and properties. The data array should contain 9 floats per vertex. The first three floats are the coordinate point of the vertex. The second three are the vertex's color value. The last three are the vertex's normal vector (which does not have to be normalized).
 *
 * The array can represent any number of vertices, but the length (len) must be divisible by 9.
 */
Model::Model(ModelGroup* parent, float *data, int len) {
	owner = parent;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * len, data, GL_STATIC_DRAW);
}

Model::~Model() {
	glDeleteBuffers(1, &vbo);
}

} /* namespace gl3d */
