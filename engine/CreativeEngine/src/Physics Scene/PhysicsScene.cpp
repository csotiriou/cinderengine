//
// Created by Christos Sotiriou on 26/08/2017.
//

#include "PhysicsScene.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

void PhysicsScene::setup() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    
    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new    btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    
    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;
    
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
    
    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));

}

void PhysicsScene::draw() {

}

void PhysicsScene::onResize() {
    Scene::onResize();
}

PhysicsScene::~PhysicsScene() {
    delete dispatcher;
    delete collisionConfiguration;
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
}
