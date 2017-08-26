//
// Created by Christos Sotiriou on 26/08/2017.
//

#include "MainScene.h"

using namespace ci;
using namespace ci::app;

void MainScene::setup() {
    mLightPosition = vec3(10,10,10);
    
    auto teapotMesh = TriMesh::create(geom::Teapot());
    auto planeMesh = TriMesh::create(geom::Plane());
    
    auto texture = gl::Texture::create( ip::checkerboard( 512, 512, 32 ) );
    auto glslDefault = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
    auto glslPsychedelic = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );

    auto mBoundingSphere = Sphere::calculateBoundingSphere(teapotMesh->getPositions<3>(), teapotMesh->getNumVertices());
    mCam = mCam.calcFraming(mBoundingSphere);
    

    teapot = DrawableRef(new Drawable(teapotMesh, glslDefault, texture));
    plane = DrawableRef(new Drawable(planeMesh, glslDefault, texture));
}

void MainScene::draw() {
    float spinAngle = (float) app::getElapsedSeconds();
    auto plane = geom::Plane();



    auto identity = cinder::quat();
    auto rotation = cinder::rotate(identity, cinder::toRadians(spinAngle), vec3(0,1,0));


    gl::pushMatrices();
    {
        gl::rotate(rotation);
        (*this->plane).mGlsl->uniform("lightPosition", mLightPosition);
        (*this->plane).mGlsl->uniform("time", spinAngle);
        (*this->plane).draw();
    }
    gl::popMatrices();

    gl::pushMatrices();
    {
        (*this->teapot).mGlsl->uniform("lightPosition", mLightPosition);
        this->teapot->draw();
    }
    gl::popMatrices();
}

void MainScene::onResize() {
    Scene::onResize();
    mCam.setAspectRatio(getWindowAspectRatio());
}
