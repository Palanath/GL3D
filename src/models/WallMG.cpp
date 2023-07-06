/*
 * WallMG.cpp
 *
 *  Created on: Jul 5, 2023
 *      Author: Palanath
 */

#include "WallMG.h"

inline namespace {
constexpr const char *const VERTEX_SHADER = R"(#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vertColor;
layout(location = 2) in vec3 normvec;

out vec3 position;
out vec3 pointColor;
out vec3 normalVector;

void main() {
	gl_Position = vec4(position = pos, 1);
	normalVector = normvec;
	pointColor = vertColor;
}
)", *const FRAGMENT_SHADER = R"(#version 330 core
	uniform vec3 lightloc;
	uniform vec3 lightColor;
	uniform vec3 ambientLightColor;
	uniform vec3 lightAttenuation;

	in vec3 position;
	in vec3 pointColor;
	in vec3 normalVector;

	out vec4 color;

	void main() {
		const float materialAmbientReflectivity = 0.08;

		vec3 pointToLightVector = lightloc - position;
		float lightSourceDistance = length(pointToLightVector);

		vec3 ambientTerm = materialAmbientReflectivity * ambientLightColor;

		float attenuation = 1 / (lightAttenuation.x + lightAttenuation.y * lightSourceDistance + lightAttenuation.z * lightSourceDistance * lightSourceDistance);
		float diffuseDotProd = dot(normalize(pointToLightVector), normalize(normalVector));
		vec3 diffuseTerm = diffuseDotProd < 0 ? vec3(0,0,0) : pointColor * diffuseDotProd * lightColor * attenuation;
		color = vec4(ambientTerm + diffuseTerm, 1);
	}
)";
}

namespace gl3d::models {

WallMG::WallMG() :
		ModelGroup(VERTEX_SHADER, FRAGMENT_SHADER) {
}

WallMG::~WallMG() {
}

} /* namespace gl3d::models */
