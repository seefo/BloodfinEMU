/*
 * DarkFrsMenuComponent.h
 *
 *  Created on: 05/18/2014
 *      Author: Skyyyr Death
 */

#ifndef LIGHTFRSMENUCOMPONENT_H_
#define LIGHTFRSMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
	class SceneObject;
}
}
}
}

using namespace server::zone::objects::scene;

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

class LightFrsMenuComponent : public TangibleObjectMenuComponent {
public:
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);

	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

};


#endif /* LightFrsMENUCOMPONENT_H_ */
