/*
 * WallMG.cpp
 *
 *  Created on: Jul 5, 2023
 *      Author: Palanath
 */

#include "WallMG.h"

inline namespace {
constexpr char *const VERTEX_SHADER = "", *const FRAGMENT_SHADER = "";
}

namespace gl3d::models {

WallMG::WallMG() :
		ModelGroup(VERTEX_SHADER, FRAGMENT_SHADER) {
}

WallMG::~WallMG() {
}

} /* namespace gl3d::models */
