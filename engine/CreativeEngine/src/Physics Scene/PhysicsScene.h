//
// Created by Christos Sotiriou on 26/08/2017.
//

#ifndef CREATIVEENGINE_PHYSICSSCENE_H
#define CREATIVEENGINE_PHYSICSSCENE_H


#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "Scene.h"

class PhysicsScene : public Scene {
    btCollisionDispatcher* dispatcher;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btBroadphaseInterface* overlappingPairCache;

public:
    ~PhysicsScene();
    void setup() override;
    void draw() override;
    void onResize() override;
    
};


#endif //CREATIVEENGINE_PHYSICSSCENE_H
