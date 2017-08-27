//
// Created by Christos Sotiriou on 27/08/2017.
//

#include "LevelScene.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace ci;
using namespace ci::app;

void LevelScene::setup() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    
    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new    btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    
    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;
    
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));

    createPlane();
    createAllCubes();
}

void LevelScene::draw() {
    
    dynamicsWorld->stepSimulation((ci::app::getElapsedFrames() / ci::app::getElapsedSeconds()));
    
    
    
    std::cout << this->drawables[0]->positionInWorld.x << " ";
    std::cout << this->drawables[0]->positionInWorld.y << " ";
    std::cout << this->drawables[0]->positionInWorld.z <<  "\n";

    for (int i = 0; i< this->dynamicsWorld->getNumCollisionObjects(); i++) {
        btCollisionObject* obj = this->dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        
        if (body && body->getMotionState()){
            btTransform trans;
            body->getMotionState()->getWorldTransform(trans);
            
            
            void *userPointer = body->getUserPointer();
            
            if (userPointer) {
                btQuaternion orientation = trans.getRotation();
                btVector3 origin = trans.getOrigin();
                
                
                auto currentDrawable = static_cast<Drawable *>(userPointer);
                currentDrawable->positionInWorld = vec3(origin.x(), origin.y(), origin.z());

                
                auto quat = glm::quat(orientation.getW(), glm::vec3(orientation.getX(), orientation.getY(), orientation.getZ()));
                currentDrawable->rotationInWorld = glm::toMat4(quat);
            }

        }
    }
    
    for (auto &d : this->drawables) {
        d->draw();
    }
}

void LevelScene::onResize() {
    Scene::onResize();
    mCam.setAspectRatio(getWindowAspectRatio());
}

void LevelScene::createAllCubes() {
    auto texture = gl::Texture::create( ip::checkerboard( 512, 512, 32 ) );
    auto glslDefault = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );

    auto pointVector = std::vector<vec3>();

    int numberOfCubesPerSide = 10;
    float yOffset = 100;

    for (int i = 0; i < numberOfCubesPerSide; i++) {
        for (int j = 0; j < numberOfCubesPerSide; j++) {
            for (int z = 0; z < numberOfCubesPerSide; z++) {
                auto cubeSize = vec3(1.0,1.0,1.0);
                auto cubePosition = vec3(i, j + yOffset, z);

                auto cubeMesh = TriMesh::create(geom::Cube().size(cubeSize));
                auto newDrawable = new Drawable(cubeMesh, glslDefault, texture);
                auto newDrawableRef = DrawableRef(newDrawable);
                newDrawableRef->positionInWorld = cubePosition;
                this->drawables.push_back(newDrawableRef);

                pointVector.push_back(vec3(i, j, z));

                btScalar    mass(1.f);
                newDrawable->name = "" + std::to_string(i) + "" + std::to_string(j) + "" + std::to_string(z);

                btCollisionShape* colShape = new btBoxShape(btVector3(cubeSize.x / 2, cubeSize.y / 2, cubeSize.z / 2));
                
                m_collisionShapes.push_back(colShape);

                /// Create Dynamic Objects
                btTransform startTransform;
                startTransform.setIdentity();
                startTransform.setOrigin(btVector3(cubePosition.x, cubePosition.y,cubePosition.z));

                auto newBody = createRigidBody(mass,startTransform,colShape);
                newBody->setUserPointer(newDrawable);
            }
        }
    }


}

void LevelScene::createPlane() {
    btBoxShape* groundShape = createBoxShape(btVector3(btScalar(50.),btScalar(1.),btScalar(50.)));
    m_collisionShapes.push_back(groundShape);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-2,0));
    btScalar mass(0.);
    createRigidBody(mass,groundTransform,groundShape, btVector4(0,0,1,1));
}

btBoxShape *LevelScene::createBoxShape(const btVector3 &halfExtents) {
    btBoxShape* box = new btBoxShape(halfExtents);
    return box;
}

btRigidBody *LevelScene::createRigidBody(float mass, const btTransform &startTransform, btCollisionShape *shape, const btVector4 &color) {
    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    

    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);
    btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

    btRigidBody *body = new btRigidBody(cInfo);
    body->setRestitution(btScalar(0.1));
    body->setUserIndex(-1);
    dynamicsWorld->addRigidBody(body);
    return body;
}


