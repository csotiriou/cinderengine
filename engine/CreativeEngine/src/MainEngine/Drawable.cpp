//
// Created by Christos Sotiriou on 26/08/2017.
//

#include "Drawable.h"


Drawable::Drawable(TriMeshRef trimesh, gl::GlslProgRef glslProgram, gl::TextureRef texture) {
    mGlsl = glslProgram;
    mBatch = gl::Batch::create( *trimesh, mGlsl );
    mTexture = texture;
}

void Drawable::draw() {
    gl::ScopedModelMatrix modelMatrix;//push the matrices
    
    gl::ScopedTextureBind textureBind(mTexture);

    mat4 currentMatrix = mat4();
    currentMatrix = glm::translate(currentMatrix, positionInWorld);
    currentMatrix *= rotationInWorld;
    
    gl::setModelMatrix(currentMatrix);
    
    mBatch->draw();

}
