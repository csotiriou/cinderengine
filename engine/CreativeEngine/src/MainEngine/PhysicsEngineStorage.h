//
// Created by Christos Sotiriou on 27/08/2017.
//

#ifndef CREATIVEENGINE_PHYSICSENGINESTORAGE_H
#define CREATIVEENGINE_PHYSICSENGINESTORAGE_H

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

class PhysicsEngineStorage {

public:
    btCollisionDispatcher* dispatcher;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btBroadphaseInterface* overlappingPairCache;

    btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

    ~PhysicsEngineStorage() {

        for (int j=0;j<m_collisionShapes.size();j++)
        {
            btCollisionShape* shape = m_collisionShapes[j];
            m_collisionShapes[j] = 0;
            delete shape;
        }

        //delete dynamics world
        delete dynamicsWorld;

        //delete solver
        delete solver;

        //delete broadphase
        delete overlappingPairCache;

        //delete dispatcher
        delete dispatcher;

        delete collisionConfiguration;

        m_collisionShapes.clear();
    }

    btRigidBody*    registerRigidBody(float mass, const btTransform &startTransform, btCollisionShape *shape, const btVector4 &color = btVector4(1, 0, 0, 1));
    void            createPlane();
    btBoxShape *    createBoxShape(const btVector3 &halfExtents);

    void setup();

};

#endif //CREATIVEENGINE_PHYSICSENGINESTORAGE_H
