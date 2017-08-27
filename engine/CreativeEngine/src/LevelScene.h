//
// Created by Christos Sotiriou on 27/08/2017.
//

#ifndef CREATIVEENGINE_LEVELSCENE_H
#define CREATIVEENGINE_LEVELSCENE_H

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "Scene.h"

class LevelScene : public Scene {
    void createAllCubes();
    void createPlane();

    btBoxShape* createBoxShape(const btVector3& halfExtents);
    btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;
    btRigidBody*	createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape,  const btVector4& color = btVector4(1, 0, 0, 1));

    btCollisionDispatcher* dispatcher;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btBroadphaseInterface* overlappingPairCache;
public:
    void setup() override;

    void draw() override;

    void onResize() override;
};


#endif //CREATIVEENGINE_LEVELSCENE_H
