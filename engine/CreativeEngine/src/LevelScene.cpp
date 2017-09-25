//
// Created by Christos Sotiriou on 27/08/2017.
//

#include "LevelScene.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "CinderImGui.h"


using namespace ci;
using namespace ci::app;

void LevelScene::setup() {
    physicsEngine = std::make_shared<PhysicsEngineStorage*>(new PhysicsEngineStorage());
    
    
    
    (*physicsEngine)->setup();

    (*physicsEngine)->createPlane();
    createAllCubes();
}

void LevelScene::draw() {
    
    (*physicsEngine)->dynamicsWorld->stepSimulation((ci::app::getElapsedFrames() / ci::app::getElapsedSeconds()));
    
    for (int i = 0; i< (*physicsEngine)->dynamicsWorld->getNumCollisionObjects(); i++) {
        btCollisionObject* obj = (*physicsEngine)->dynamicsWorld->getCollisionObjectArray()[i];
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
    ui::Text("number of objects: %lu", this->drawables.size());
    
}

void LevelScene::onResize() {
    Scene::onResize();
    mCam.setAspectRatio(getWindowAspectRatio());
}

void LevelScene::createAllCubes() {
    auto cubeSize = vec3(1.0,1.0,1.0);
    
    auto texture = gl::Texture::create( ip::checkerboard( 512, 512, 32 ) );
    auto glslDefault = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
    auto cubeMesh = TriMesh::create(geom::Cube().size(cubeSize));
    auto pointVector = std::vector<vec3>();

    int numberOfCubesPerSide = 10;
    float yOffset = 100;

    for (int i = 0; i < numberOfCubesPerSide; i++) {
        for (int j = 0; j < numberOfCubesPerSide; j++) {
            for (int z = 0; z < numberOfCubesPerSide; z++) {
                
                auto cubePosition = vec3(i, j + yOffset, z);

                
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

                auto newBody = (*physicsEngine)->registerRigidBody(mass, startTransform, colShape);
                newBody->setUserPointer(newDrawable);
            }
        }
    }
}

