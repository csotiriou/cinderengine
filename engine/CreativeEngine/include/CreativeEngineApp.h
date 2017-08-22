#pragma once

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
    
    Drawable(TriMeshRef trimesh, gl::GlslProgRef glslProgram, gl::TextureRef texture) {
        mGlsl = glslProgram;
        mBatch = gl::Batch::create( *trimesh, mGlsl );
        mTexture = texture;
    }

    void draw() {
        mTexture->bind( 0 );
        mBatch->draw();
        mTexture->unbind();
    }

};

class CreativeEngineApp : public cinder::app::AppCocoaView {
    CameraPersp        mCam;
    Sphere            mBoundingSphere;

    std::vector<Drawable> drawables;

  public:
	void				setup();
	void				draw();

	float				mRadius;
	cinder::Colorf		mColor;
};
