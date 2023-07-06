/*
 * WallModel.h
 *
 *  Created on: Jul 6, 2023
 *      Author: Palanath
 */

#ifndef MODELS_WALLMODEL_H_
#define MODELS_WALLMODEL_H_

#include "../Model.h"
#include "../ModelGroup.h"

namespace gl3d::models {

class WallModel: public Model {
public:
	WallModel(ModelGroup*);
	virtual ~WallModel();
};

} /* namespace gl3d::models */

#endif /* MODELS_WALLMODEL_H_ */
