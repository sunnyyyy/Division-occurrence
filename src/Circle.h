//
//  Circle.h
//  AV_Final
//
//  Created by Sunny Liao on 2021/4/18.
//

#ifndef Circle_h
#define Circle_h
#include "ofMain.h"

using namespace std;
class Circle {

public:
    Circle();

    void update();
    void draw(int x,int y,int currentpitch);
    void interpolateByPct(float myPct);
    int numSqX = 24;
    int numSqY = 12;
    
    int spacingX;
    int spacingY;
    int startX;
    int startY;
private:
    int radius;
    int top;
    int left;

    float secondsAngle;
    float minutesAngle;
    float hoursAngle;

};

#endif /* Circle_h */
