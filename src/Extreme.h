#pragma once

#include "ofMain.h"
//https://www.openprocessing.org/sketch/397343

using namespace glm;

class Extreme {
public:
    Extreme();
    void setup(ofVec2f pos);
    void update();
    void draw(float y);
    
    ofVec2f pos;//position of sphere
    ofVec2f origin;//initial Xposition
    int lastFrameChangeTime;//parameter to random the animation movement
    float changeTime;//animation movement time period
    float goX;//parameter to hold random xPos
    float pulse;//pulse for animation
    float delay;//delay effect
    ofVec2f getPos();//get pos of sphere for calculation
    float getPulse();//get the pulse period of time


};
