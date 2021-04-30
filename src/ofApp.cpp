#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();
    ofSetCircleResolution(100);
    dir.setup();//ofxSyphon directory setup
    mClient.setup();//ofxSyphon client
    tex.allocate(1024, 768, GL_RGBA);//allocate the texture
    
    //using Syphon app Simple Server for high quality recording
    mClient.set("","Simple Server");
    //register for our directory's callbacks
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    //ofAddListener(dir.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    dirIdx = -1;

    /* lightning setup */
    this->light.setPosition(200, 0, 600);
    this->light.setAreaLight(1024, 1024);
    this->light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    this->light.setDiffuseColor(ofFloatColor(0.8, 0.8, 0.8));
    this->light.setAmbientColor(ofFloatColor(0.2, 0.2, 0.2));
    this->light.enable();
    
    /* font setup */
    ofTrueTypeFontSettings typesettings("PixelArial.TTF",15);
    typesettings.antialiased = true;
    typesettings.contours = true;
    typesettings.dpi = 72;
    typesettings.addRanges(ofAlphabet::Chinese);
    typesettings.addRanges(ofAlphabet::Latin);
    typesettings.addRanges(ofAlphabet::Greek);
    ttf.load(typesettings);

    /* ofxMaxim setup */
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size */
    numbercount=0;
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    //sets up the soundStream object with default devices
    auto devices = soundStream.getMatchingDevices("default");
    //you can also list input/output devices with soundStream.printDeviceList()
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0;
    soundSettings.bufferSize = bufferSize;
    soundStream.setup(soundSettings);
    
    myEnvelope.setAttack(0);
    myEnvelope.setDecay(1);  // Needs to be at least 1
    myEnvelope.setSustain(1);
    myEnvelope.setRelease(1000);
    
    wavesize=4096;
    level=0;
    
    iteration=0; //iteration counter
    animation.setup();// proportion animation setup
    numOfTiles=10;
    maxBufferSize = numOfTiles * numOfTiles;
    Pix.allocate(ofGetWidth(),ofGetHeight(), OF_PIXELS_RGB); //width, height, number of channels

    ofEnableSmoothing();
    ofSetVerticalSync(true);
    
    /* camera setup */
    camera.setPosition(ofGetWidth()/2,ofGetHeight()/2,0);
    camera.setVFlip(true);
    
    /* Osc setup */
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    }

//--------------------------------------------------------------
void ofApp::update(){
    
    ofImage img;
    img.setFromPixels(Pix);

    /* update drawing level each frame */
    if(level<16){
        level+=1;
    }
    
    else{
        level=0;
    }
    /* animation update */
    animation.update();
    
    /* update scanning line each frame */
    if(scan<ofGetWidth()){scan+=5;}
    else scan=0;
    
    /* osc message update */
    if (messageBuffer.size()>maxBufferSize) messageBuffer.pop_back();

    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // check for touch osc accelerometer
        if(m.getAddress() == "/accxyz"){
            // three argument are floats
            xx = m.getArgAsFloat(1);
            yy = m.getArgAsFloat(2);
            zz = m.getArgAsFloat(3);
           
            //map the number to x,y position
            mouseX=ofMap(filter3.lopass(xx, 0.5), -1, 1, 0, ofGetWidth());
            mouseY=ofMap(filter3.lopass(yy, 0.5), -1, 1, 0, ofGetHeight());
        }
    }
    
    /* camera movement based on mouse position */
    // camera look at the center of graphic
    ofVec3f center(ofGetWidth()/2*sin(1),ofGetHeight()/2*sin(1),0);
    
    //rotateamount based on mouseX (from touchosc)
    float rotateAmount = ofMap(mouseX, 0, ofGetWidth(), 0, 360);
   
    ofVec3f furthestPoint;
    if (points.size() > 0) {
        furthestPoint = points[0];
    }
    else
    {
        furthestPoint = ofVec3f(mouseX, mouseY, 0);
    }
    
    // calculate the distance between center and furtherstpoint
    ofVec3f directionToFurthestPoint = (furthestPoint - center);
    ofVec3f directionToFurthestPointRotated = directionToFurthestPoint.getRotated(rotateAmount, ofVec3f(0,1,0));
    camera.setPosition(center + directionToFurthestPointRotated);
    camera.lookAt(center);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofxOscMessage m;

    
    //spectrum drawing grid
    int width=ofGetWidth()/128;
    int height=ofGetHeight()/16;
    
    //map the pitch to drawing position
    int x=ofMap(pitch[playHead%8], 20, 400, 50, ofGetWidth()-100);
    int y=ofMap(pitch[playHead%8], 20, 800,50, ofGetHeight()-100);
    int z=ofMap(pitch[playHead%8], 20, 800,-50, 50);
    
    camera.begin();
    // Draw the sound spectrum when iteration<5
    if(iteration<5){
    for(int j=0;j<ofGetWidth();j=j+width){
        ofFill();
        ofSetColor(255, 255, 255, 255*waveform[j]);
        ofDrawRectangle(j, height*level, width, height);
        ofSetColor(255, 0, 0);
        ofSetLineWidth(3);
        ofDrawLine(scan,0,scan,ofGetHeight());
        ofSetColor(0);
        ofDrawRectangle(scan, 0, ofGetWidth()-scan, ofGetHeight());
        //Draw white rectangle at pitch[8]
        if(playHead%8==0){
            ofSetColor(255);
            ofDrawRectangle(0, 0, scan, ofGetHeight());
           }
        }
    }
    
    // Draw the sound spectrum of 2D line and 3D box
    if(iteration>5&&iteration<7){
        for(int j=ofGetWidth();j>0;j=j-width){
            ofSetColor(255);
            ofNoFill();
            int width=waveform[j]*20;
            ofSetLineWidth(width);//Line width based on waveform
            ofDrawLine(height*level, j, 0, height*level, j-width, width);
            if(playHead%8==0){
            ofSetColor(255);
                ofDrawBox(j, height*level, 0, j-width+10, height*level, width-10);
          }
        }
    }
    
    //Draw the proportion animation
    if(iteration>7&&iteration<11){
    animation.draw();
    }
    
    //Draw the bezier curve based on pitch
    if(iteration>11){
     
        for(int i=0;i<playHead;i++){
            
            ofBeginShape();
            int x0=ofMap(pitch[0], 20, 400, 50, ofGetWidth()-100);
            int y0=ofMap(pitch[0], 20, 800, 50, ofGetHeight()-100);
            int x1=ofMap(pitch[i], 20, 400, 50, ofGetWidth()-100);
            int y1=ofMap(pitch[i], 20, 800, 50, ofGetHeight()-100);
           
            //mapping the pitch as xy position and push it in vector
            points.push_back(glm::vec2(x,y));
            
            //set different color based on iteration
            if(iteration<15){
            ofSetColor(255, 255, 255, 255*waveform[i]);
            }
            else{
                ofSetBackgroundColor(200);
                ofSetColor(0, 0, 0, 255*waveform[i]);
            }
            
            //dist of current pitch and previous pitch
            float dist=pitch[(playHead%8)+1]-pitch[playHead%8];
            ofSetLineWidth(1);
            ofNoFill();
            for (int deg = 0; deg < 360; deg += 5) {
            ofVertex(x * cos(deg * DEG_TO_RAD)+ ofGetWidth() * 0.5, y1 * sin(deg * DEG_TO_RAD)+ ofGetHeight() * 0.5);
            }
            ofEndShape();
            
            //Draw the center of the shape
            ofSetColor(200, 0, 0, 255*waveform[i]);
            ofSetLineWidth(2);
            ofDrawLine(ofGetWidth()/2, 0,ofGetWidth()/2 , ofGetHeight());
            ofDrawLine(0, ofGetHeight()/2,ofGetWidth(), ofGetHeight()/2);

        }
        
        //Draw the pitch number
        ofSetColor(255);
        string myChar = ofToString(pitch[playHead%8]);
        ttf.drawString(myChar, 800, 200);

    }
    
    //Draw the YZ grid plane
    if(iteration>10){
        if(iteration>15){
            ofSetColor(0);
        }
        ofDrawGridPlane(500, ofGetHeight()/2, true);
    }

    camera.end();
    
    //Draw the mouseX mouseY position
    char fre[255];
    sprintf(fre, "%d /",int(mouseX));
    ofSetColor(0,230,0);
    ttf.drawString(fre, mouseX+10,mouseY);
    numbercount=playHead/8;
    
    char fpsStr[255]; // an array of chars
    sprintf(fpsStr, "%d", int(mouseY));
    ofSetColor(0,230,0);
    ttf.drawString(fpsStr, mouseX+60,mouseY);
    
    //Draw the position of current mouse position
    ofSetColor(200);
    ofDrawCircle(mouseX, mouseY, 2);
    if(playHead%8==0){
        ofSetColor(255, 0, 0);
    }else ofSetColor(200);
    ofDrawLine(mouseX, 0, mouseX, ofGetHeight());
    ofDrawLine(0, mouseY, ofGetWidth(), mouseY);
  
    
    // Syphon Stuff
    if(dir.isValidIndex(dirIdx))
    mClient.draw(0, 0);
    
    mainOutputSyphonServer.publishScreen();
    individualTextureSyphonServer.publishTexture(&tex);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    
    std::size_t outChannels = output.getNumChannels();
    
    for (int i = 0; i < output.getNumFrames(); ++i){
        currentCount=(int)timer.phasor(7);//this sets up a metronome that ticks every so often
        
        if (lastCount!=currentCount) {//if we have a new timer int this sample, play the sound
            trigger=1;//play the arpeggiator line
            trigger2=leadLineTrigger[playHead%256];//play the lead line
            if (trigger2==1) {//if we are going to play a note
                leadPitch=leadLinePitch[newnote];//get the next pitch val
                newnote++;//and iterate
                if (newnote>14) {
                    newnote=0;//make sure we don't go over the edge of the array
                    
                }
            }
            currentPitch=pitch[(playHead%8)]+chord[currentChord%16];//write the frequency val into currentPitch
            playHead++;//iterate the playhead
            
            if (playHead%16==0) {//wrap every 4 bars
                currentChord++;//change the chord
                iteration++;
            }
            lastCount=0;//set lastCount to 0
        }
        
        bassout=envelope.adsr(sound.sinewave(currentPitch),1,0.9995, 0.95, 0.9995, 1, trigger);// simple ADSR.
                
        out1=filter2.lores(bassout,mouseX*10,ofMap(mouseY, 0, ofGetHeight(), 0, 60));// lowpass bassout with cutoff point base on mouseX and resonance based on mouseY
        
        leadout=filter.lores(bassout,1900,1);//leadline
      
        
        delayout=(leadout+(delay.dl(leadout, 14000, 0.8)*0.9))/2;//add some delay
    
        if(trigger!=0)trigger=0;//set the trigger to off if you want it to trigger immediately next time.
        
        
        output[i * outChannels]=out1*0.3;
        output[i * outChannels + 1] = out1*0.3;
   
        //store waveform in array
        waveform[waveIndex] =  output[i * outChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        } else {
            waveIndex = 0;
        }
      

    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
//ofxSyphon class
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}
