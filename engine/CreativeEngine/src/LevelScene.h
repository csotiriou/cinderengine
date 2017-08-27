//
// Created by Christos Sotiriou on 27/08/2017.
//

#ifndef CREATIVEENGINE_LEVELSCENE_H
#define CREATIVEENGINE_LEVELSCENE_H

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "Scene.h"
#include "PhysicsEngineStorage.h"

using std::make_shared;


class LevelScene : public Scene {
    void createAllCubes();
    void createPlane();

    btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

    std::shared_ptr<PhysicsEngineStorage *> physicsEngine;
public:
    void setup() override;

    void draw() override;

    void onResize() override;
};


#endif //CREATIVEENGINE_LEVELSCENE_H
