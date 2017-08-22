#include "CreativeEngineApp.h"
#include "cinder/gl/gl.h"
#include "cinder/Sphere.h"
#include <assimp/Importer.hpp>

using namespace ci;
using namespace ci::app;

void CreativeEngineApp::setup()
{
	mRadius = 50;
	mColor = Color( 1.0f, 0.5f, 0.25f );


    auto teapotMesh = TriMesh::create(geom::Teapot());
    auto planeMesh = TriMesh::create(geom::Plane());
    
    mBoundingSphere = Sphere::calculateBoundingSphere(teapotMesh->getPositions<3>(), teapotMesh->getNumVertices());
    mCam = mCam.calcFraming(mBoundingSphere);
    
    
    auto texture = gl::Texture::create( ip::checkerboard( 512, 512, 32 ) );
    auto glslDefault = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
    auto glslPsychedelic = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "psychedelicShader.frag" ) );
    
    
    drawables.push_back(Drawable(teapotMesh, glslPsychedelic, texture));
    drawables.push_back(Drawable(planeMesh, glslDefault, texture));
}

void CreativeEngineApp::draw()
{
    float spinAngle = (float) app::getElapsedSeconds();
    auto plane = geom::Plane();
    
    
    gl::enableDepthWrite();
    gl::enableDepthRead();
    
    gl::clear( Color( 0.0f, 0.1f, 0.2f ) );
    
    gl::setMatrices( mCam );
    
    auto identity = cinder::quat();
    auto rotation = cinder::rotate(identity, cinder::toRadians(spinAngle), vec3(0,1,0));
    
    gl::pushMatrices();
    {
        gl::rotate(rotation);
        this->drawables[0].mGlsl->uniform("time", spinAngle);
        this->drawables[1].draw();
    }
    gl::popMatrices();
    
    gl::pushMatrices();
    {
        this->drawables[0].draw();
    }
    gl::popMatrices();
}




