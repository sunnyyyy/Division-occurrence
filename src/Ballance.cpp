#include "Ballance.h"


//--------------------------------------------------------------
 Ballance::Ballance() {
  

}
//--------------------------------------------------------------
void Ballance::setup(){
      velX = 0;
      prevX = 0;
      amplitude=10;
      pos1.set(ofGetWidth()/2, ofGetHeight()/2);//initialise position

}


//--------------------------------------------------------------
void Ballance::update(float x) {
 
    pos1.x += (x - pos1.x) * 0.05;//update the position that kept bouncing between two points
   
}

//--------------------------------------------------------------
void Ballance::draw(float y) {
    
   float y1 = pos1.y+y*amplitude;//jumping value
   velX = (prevX-pos1.x);//velocity calculation from previous x position
   
   ofSetColor(255);
   ofFill();
   ofPushMatrix();
   ofTranslate(pos1.x, y1);//translate to the updated position
   ofRotate(velX*40);//add extra rotation to do the same in processing
   ofDrawRectangle(-5, 0, 10, -30);
   ofPopMatrix();
   prevX = pos1.x;//assign current position to previous position
    
}

//--------------------------------------------------------------
ofVec2f Ballance::getPos1() {
    
    return pos1;
}
