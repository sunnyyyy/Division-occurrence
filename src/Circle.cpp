//
//  Circle.cpp
//  AV_Final
//
//  Created by Sunny Liao on 2021/4/18.
//

#include "Circle.h"

Circle::Circle()
{
    //Make everything looking nice and smooth.
    ofSetCircleResolution(100);
    ofEnableSmoothing();

    //Set size & position of the clock
    if( ofGetHeight() < ofGetWidth() )
        radius = 50;
    else
        radius = 50;
    
    top = 50;
    left = 50;
    
    spacingX = ofGetWidth()/ numSqX;
    spacingY = ofGetHeight() / numSqY;
    startX = spacingX/2;
    startY = spacingY/2;
}

void Circle::update(){
    
 
}

void Circle::draw(int x, int y,int currentpitch){
    
    
    //The length of the hands of clock are based on the mouse position
    ofSetColor(255);
    ofSetLineWidth(3);
    ofNoFill();
    int size=ofMap(currentpitch, 0, 300, 0, 1);
    for (int i = 0; i < numSqX ; i++)   {
        for (int j = 0; j < numSqY; j++)    {
            int locX = startX * i + 200;
            int locY = startY + spacingY * j + 10;
            
    ofPushMatrix();
    ofTranslate(locX, locY);
    ofDrawCircle(0, 0, radius*size);
    ofPopMatrix();
            
        }
    }

    //Set the coordinatesystem to the center of the clock.
    ofPoint circle_center = ofPoint( x,y );
  
    
    
    
}


