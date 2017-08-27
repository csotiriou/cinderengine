//
// Created by Christos Sotiriou on 26/08/2017.
//

#ifndef CREATIVEENGINE_DRAWABLE_H
#define CREATIVEENGINE_DRAWABLE_H

#include "cinder/app/cocoa/AppCocoaView.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ip/Checkerboard.h"
#include <vector>


using namespace cinder;


class Drawable {
public:
    gl::BatchRef        mBatch;
    gl::GlslProgRef    mGlsl;
    gl::TextureRef    mTexture;

    vec3 positionInWorld;
    mat4 rotationInWorld;
    std::string name;

    Drawable(TriMeshRef trimesh, gl::GlslProgRef glslProgram, gl::TextureRef texture);
    void draw();
};

typedef std::shared_ptr<Drawable> DrawableRef;

#endif //CREATIVEENGINE_DRAWABLE_H
