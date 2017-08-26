#include "CreativeEngineApp.h"
#include "cinder/gl/gl.h"
#include "cinder/Sphere.h"
#include <assimp/Importer.hpp>
#include "MainScene.h"

using namespace ci;
using namespace ci::app;

void CreativeEngineApp::setup()
{
    currentScene.reset(new MainScene());
    currentScene->setup();
}

void CreativeEngineApp::draw()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();
    
    gl::clear( Color( 0.0f, 0.1f, 0.2f ) );
    
    gl::setMatrices( currentScene->mCam );
    this->currentScene->draw();
}

void CreativeEngineApp::resize() {
    AppBase::resize();
    this->currentScene->onResize();
}




