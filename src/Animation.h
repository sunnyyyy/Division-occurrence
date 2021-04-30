#pragma once

#include "ofMain.h"
#include "Extreme.h"
#include "Ballance.h"
#include "ofTrueTypeFont.h"
////coding reference https://www.openprocessing.org/sketch/397343


class Animation{

	public:
		void setup();
		void update();
		void draw();

    //initialise all the parameters
    ofPath p ;
    float centerX, centerY;
    float amplitude;
    Extreme extreme1;//circle 1
    Extreme extreme2;//circle 2
    Ballance ballance;//middle rectangle
    float cardiogram(float percent, float time);//fomula that calculates the movement
    ofTrueTypeFont portion;

  
};

