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
Model::Model(ModelGroup *parent, float *data, int len) {
	owner = parent;
	verts = len / 9;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * len, data, GL_STATIC_DRAW);
	parent->configureModel(*this);
}

/*
 * Prepares to draw this model, then draws it.
 *
 * This member function calls this Model's owning ModelGroup's prepareForRender() member function, which sets up the VAO and Shader Program, for the model group, to be used.
 * Then this function calls Model::draw(), which binds the VBO and draws the associated vertices.
 *
 * This function is a convenience function used to render this Model without rendering others in the same group.
 * It sets up the VAO and shader program through the owning ModelGroup for that reason.
 * However, if many Models of the same group are to be rendered in sequence, overhead calls can be avoided by invoking the ModelGroup's prepareForRender() member function once, and then calling the draw() member function on each model in sequence.
 */
void Model::render() {
	owner->prepareForRender();
	draw();
}

/*
 * Draws this Model, assuming that the ModelGroup it belongs to is currently the active group being rendered (in that ModelGroup::prepareForRender() has been called to set the vertex array and program it contains as active).
 */
void Model::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(GL_TRIANGLES, 0, verts);
}

Model::~Model() {
	glDeleteBuffers(1, &vbo);
}

} /* namespace gl3d */
