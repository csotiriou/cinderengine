//
// Created by Christos Sotiriou on 26/08/2017.
//

#ifndef CREATIVEENGINE_SCENE_H
#define CREATIVEENGINE_SCENE_H


#include "Drawable.h"

class Scene {
protected:
    cinder::vec3    mLightPosition;
    std::vector<Drawable> drawables;
public:
    CameraPersp        mCam;

    virtual void setup() = 0;
    virtual void draw() = 0;

    virtual void onResize() {}
};


#endif //CREATIVEENGINE_SCENE_H
