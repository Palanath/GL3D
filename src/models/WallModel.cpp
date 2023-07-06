/*
 * WallModel.cpp
 *
 *  Created on: Jul 6, 2023
 *      Author: Palanath
 */

#include "WallModel.h"

inline namespace {
constexpr const float WALL_DATA[] = {
	-1, 1, 1,    .3, .3, .3,    0, 0, -1,
	-1, -1, 1,   0, .3, 1,    0, 0, -1,
	1, -1, 1,    1, 0, 1,    0, 0, -1
};
}

namespace gl3d::models {

WallModel::WallModel(ModelGroup *parent) :
		Model(parent, WALL_DATA, sizeof WALL_DATA / sizeof(float)) {
}

WallModel::~WallModel() {
}

} /* namespace gl3d::models */
