#include "ofApp.h"
#include "Animation.h"

//--------------------------------------------------------------
void Animation::setup(){
    centerX = ofGetWidth()/2;
    centerY = ofGetHeight()/2;
    //initialise the position to the center of the window
    ofVec2f firstpos1(centerX-centerX/2, centerY);
    ofVec2f firstpos2(centerX+centerX/2, centerY);
    
    extreme1.setup(firstpos1);//sets the graphic start from the middle of the vanvas
    extreme2.setup(firstpos2);//sets the graphic start from the middle of the vanvas
    ballance.setup();
    p.setMode(ofPath::POLYLINES);
    amplitude=10;
    
    //type setup
    ofTrueTypeFontSettings typesettings("PixelArial.TTF",40);
    typesettings.antialiased = true;
    typesettings.contours = true;
    typesettings.dpi = 72;
    typesettings.addRanges(ofAlphabet::Chinese);
    typesettings.addRanges(ofAlphabet::Latin);
    typesettings.addRanges(ofAlphabet::Greek);

    portion.load(typesettings);
    

}

//--------------------------------------------------------------
void Animation::update(){
    
    extreme1.update();
    extreme2.update();

}

//--------------------------------------------------------------
void Animation::draw(){
    
    
   //position of X calculation
    float abism = (extreme2.getPos().x-extreme1.getPos().x);
    ballance.update(extreme1.pos.x+abism/2);//draw the square in the middle of two points
    
    int prevX = 0;
    int prevY = 0;
    
    //draw the line
    ofSetColor(0,255,0);
    ofNoFill();
    ofSetLineWidth(5);
    for(int x = extreme1.getPos().x; x < extreme2.getPos().x; x+=5){
      float percent = (x-extreme1.getPos().x)/abism;//percentage that influence the curve
      float y = centerY + amplitude * (cardiogram(percent, extreme1.getPulse()) + cardiogram(percent, 1-extreme2.getPulse()));//draw the curve
        if(prevX!=0)ofDrawLine(prevX, prevY, x, y);//Draw the line between two points
        
      prevX = x;//proceed to draw the nextpoint
      prevY = y;//proceed to draw the nextpoint
    }
    //draw the circles
    extreme1.draw(cardiogram(0.0, extreme1.pulse) + cardiogram(0.0, 1-extreme2.pulse));//point 1
    extreme2.draw(cardiogram(1.0, extreme1.pulse) + cardiogram(1.0, 1-extreme2.pulse));//point 2
    
    //draw the rectangle
    float percent = (ballance.pos1.x-extreme1.pos.x)/abism;
    ballance.draw(cardiogram(percent, extreme1.pulse) + cardiogram(percent, 1-extreme2.pulse));
    
    //calculate the number distance
    int dis1=ballance.pos1.x-extreme1.pos.x;
    int dis2=extreme2.pos.x-ballance.pos1.x;
    
    //Draw the number of the distance
    char fre[255];
    sprintf(fre, "%d",dis1);
    ofSetColor(0, 255, 0);
    portion.drawString(fre, extreme1.pos.x+30,ofGetHeight()/2);
    char fre2[255];
    sprintf(fre2,"%d",dis2);
    ofSetColor(0, 255, 0);
    portion.drawString(fre2, extreme2.pos.x-150,ofGetHeight()/2);

}

//--------------------------------------------------------------
float Animation::cardiogram(float percent, float time){
    
  //calculate the point of rectangle x position
  float d = pow((1-abs(percent-(time-0.2)*2)), 5);
  return sin(percent*TWO_PI*10.+ofGetFrameNum()/5)*d;
}
