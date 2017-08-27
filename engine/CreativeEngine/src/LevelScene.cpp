//
// Created by Christos Sotiriou on 27/08/2017.
//

#include "LevelScene.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace ci;
using namespace ci::app;

void LevelScene::setup() {
    auto glslPsychedelic = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
    createAllCubes();
}

void LevelScene::draw() {
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


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int z = 0; z < 5; z++) {
                auto cubeMesh = TriMesh::create(geom::Cube().size(vec3(0.5,0.5,0.5)));
                auto newDrawableRef = DrawableRef(new Drawable(cubeMesh, glslDefault, texture));
                newDrawableRef->positionInWorld = vec3(i, j, z);
                this->drawables.push_back(newDrawableRef);

                pointVector.push_back(vec3(i, j, z));
            }
        }
    }

    mCam = mCam.calcFraming(Sphere::calculateBoundingSphere(pointVector));

}
