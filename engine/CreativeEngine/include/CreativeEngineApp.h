#pragma once

#include "cinder/app/cocoa/AppCocoaView.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ip/Checkerboard.h"
#include "Drawable.h"
#include <vector>
#include <memory>
#include "Scene.h"

using namespace cinder;


class CreativeEngineApp : public cinder::app::AppCocoaView {
    //    CameraPersp        mCam;
    Sphere            mBoundingSphere;
    cinder::vec3    mLightPosition;
    
    std::vector<Drawable> drawables;
    
    std::shared_ptr<Scene> currentScene;
public:
    void resize() override;
    
public:
    void                setup();
    void				draw();
    
    float				mRadius;
    cinder::Colorf		mColor;
};
