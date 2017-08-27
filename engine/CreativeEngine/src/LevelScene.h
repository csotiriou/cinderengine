//
// Created by Christos Sotiriou on 27/08/2017.
//

#ifndef CREATIVEENGINE_LEVELSCENE_H
#define CREATIVEENGINE_LEVELSCENE_H


#include "Scene.h"

class LevelScene : public Scene {
    void createAllCubes();
public:
    void setup() override;

    void draw() override;

    void onResize() override;
};


#endif //CREATIVEENGINE_LEVELSCENE_H
