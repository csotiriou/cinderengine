#include "CreativeEngineApp.h"
#include "cinder/gl/gl.h"
#include "cinder/Sphere.h"
#include <assimp/Importer.hpp>
#include "MainScene.h"
#include "LevelScene.h"
#include "CinderImGui.h"

using namespace ci;
using namespace ci::app;

void CreativeEngineApp::setup()
{
    ImGui::initialize();
    currentScene.reset(new LevelScene());
    currentScene->setup();
    gl::enableVerticalSync(false);
}

void CreativeEngineApp::draw()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();
    
    gl::clear( Color( 0.0f, 0.1f, 0.2f ) );
    
    gl::setMatrices( currentScene->mCam );
    this->currentScene->draw();
    ui::Text("fps: %f", getAverageFps());
}

void CreativeEngineApp::resize() {
    AppBase::resize();
    this->currentScene->onResize();
}




