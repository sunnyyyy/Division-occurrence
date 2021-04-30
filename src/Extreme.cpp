#include "Extreme.h"

//--------------------------------------------------------------
Extreme::Extreme() {
  
    
}
//--------------------------------------------------------------
void Extreme::setup(ofVec2f newpos){
   
      lastFrameChangeTime = 0;//initialise lastframe time as 0
      changeTime = 120;
      goX = 0;//Xpos of random position
      pulse = 0;//pulse value
      delay = ofRandom(5, 30);//give random movements
      
      origin=newpos;//position set up
      pos=newpos;//position set up
    
}


//--------------------------------------------------------------
void Extreme::update() {
    
    //if condition for random movement
    if(ofGetFrameNum() - lastFrameChangeTime > changeTime+ofRandom(5, 30)){
         lastFrameChangeTime = ofGetFrameNum();
         float prevGoX = goX; //set position back to 0
         while(abs(goX-prevGoX)<30) goX = ofRandom(-100, 100);//randomize first point position 
        delay = ofRandom(0, 120);//resets delay number
       }
    
       pulse = (ofGetFrameNum() - lastFrameChangeTime) / changeTime;//update the time of pulse
    
       if(pulse>1) pulse = 1;//contro the pulse value below 1
       
       pos.x += ((origin.x+goX) - pos.x) * 0.09;//calculate the new position
   
}

//--------------------------------------------------------------
void Extreme::draw(float y) {
    ofFill();
    ofSetColor(0,255,0);
    ofDrawSphere(pos.x, pos.y+y*10, 30);


}

//--------------------------------------------------------------
ofVec2f Extreme::getPos() {
    
    return pos;
}
//--------------------------------------------------------------

float Extreme::getPulse(){
    return pulse;

}
