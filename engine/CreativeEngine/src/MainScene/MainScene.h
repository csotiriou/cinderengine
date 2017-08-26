//
// Created by Christos Sotiriou on 26/08/2017.
//

#ifndef CREATIVEENGINE_MAINSCENE_H
#define CREATIVEENGINE_MAINSCENE_H

#include "Scene.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ip/Checkerboard.h"

class MainScene : public Scene {
public:
    void setup() override;
    void draw() override;
protected:
    DrawableRef teapot;
    DrawableRef plane;
    Sphere            mBoundingSphere;
public:
    void onResize() override;
};


#endif //CREATIVEENGINE_MAINSCENE_H
