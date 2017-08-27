//
// Created by Christos Sotiriou on 27/08/2017.
//

#include "PhysicsEngineStorage.h"

btRigidBody *PhysicsEngineStorage::registerRigidBody(float mass, const btTransform &startTransform, btCollisionShape *shape, const btVector4 &color) {

    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);
    btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

    btRigidBody *body = new btRigidBody(cInfo);
    //    body->setRestitution(btScalar(.5));
    body->setUserIndex(-1);
    dynamicsWorld->addRigidBody(body);
    return body;
}

void PhysicsEngineStorage::setup() {
    collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new    btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
}

void PhysicsEngineStorage::createPlane() {
    btBoxShape* groundShape = createBoxShape(btVector3(btScalar(50.),btScalar(1.),btScalar(50.)));
    m_collisionShapes.push_back(groundShape);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-2,0));
    btScalar mass(0.);
    registerRigidBody(mass, groundTransform, groundShape, btVector4(0, 0, 1, 1));
}

btBoxShape *PhysicsEngineStorage::createBoxShape(const btVector3 &halfExtents) {
    btBoxShape* box = new btBoxShape(halfExtents);
    return box;
}
