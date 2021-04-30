#pragma once

#include "ofMain.h"

using namespace glm;

class Ballance {
public:
    Ballance();
    void setup();
    void update(float x);
    void draw(float y);

    ofVec2f pos1;
    float velX;//velocity of x position
    float prevX;//previous x position
    ofVec2f getPos1();//class that calculates the pos1
    float amplitude;
};

