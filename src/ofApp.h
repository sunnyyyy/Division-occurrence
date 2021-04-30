#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofTrueTypeFont.h"
#include "Extreme.h"
#include "Ballance.h"
#include "Animation.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"

#define PORT 8000
#define kNumTestNodes 4
#define kNumCameras 2
#define kNumLights 3
class ofApp : public ofBaseApp{

	public:
    void setup()override;
    void update()override;
    void draw()override;

    void keyPressed(int key)override;
    void keyReleased(int key)override;
    void mouseMoved(int x, int y )override;
    void mouseDragged(int x, int y, int button)override;
    void mousePressed(int x, int y, int button)override;
    void mouseReleased(int x, int y, int button)override;
    void mouseEntered(int x, int y)override;
    void mouseExited(int x, int y)override;
    void windowResized(int w, int h)override;
    void dragEvent(ofDragInfo dragInfo)override;
    void gotMessage(ofMessage msg)override;
    void reset();
    void audioOut(ofSoundBuffer& output) override;

    /* ofxMaxi*/
    ofSoundStream soundStream;
    maxiOsc oscillator1, myCounter, another,phasorsound,bass,timer,mod,lead,lead2,leadmod,osc,sound;//here are the synth bits
    double myOscOutput, myCurrentVolume;
    int currentCount,lastCount,playHead=0, currentChord=0;//some other control variables
    int trigger, trigger2, newnote;//some control variables
    maxiEnv envelope, leadenvelope;//some envelopes
    maxiFilter filter, filter2,filter3;//some filters
    maxiDelayline delay;//a delay
    convert mtof;//a method for converting midi notes to frequency
    int pitch[16]={20,40,60,50,47,30,20,300};//the bassline for the arpeggio
    int chord[8]={1,2,8,2,5,5,3,0};//the root chords for the arpeggio
    float currentPitch,leadPitch;//the final pitch variables
    double bassout,leadout, delayout, out1;//some variables to hold the data and pass it around
    //here's the lead line trigger array, followed by the pitches
    int leadLineTrigger[256]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    int leadLinePitch[15]={50,55,50,55,50,55,50,55,50,55,50,55,50,55,10};
    int CurrentCount;
    ofSoundStreamSettings soundSettings;
    ofxMaxiFFTOctaveAnalyzer oct;
    int nAverages;
    float* ifftOutput;
    int ifftSize;
    float peakFreq = 0;
    float centroid = 0;
    float RMS = 0;
    
    /*fft spectrum data */
    ofxMaxiIFFT ifft;
    ofxMaxiFFT mfft;
    int fftSize;
    int bins, dataSize;

    maxiMFCC mfcc;
    double* mfccs;
    maxiEnv myEnvelope;//some envelopes
    
    /* For drawing */
    float waveform[4096]; //storing sound
    int waveIndex;
    int wavesize;
    int numOfTiles;
    int maxBufferSize;
    ofPixels Pix,pix,pix2;//tha parameter that send data to ofxSyphon
    float scan;//number that holds the position of scanning line
    
    /* Font loading */
    ofTrueTypeFont ttf;
    int numbercount;
    int level,iteration;
    
    /* Drawing animation initialize */
    ofPath path;
    Animation animation;
    int width;
    int height;
    
    /* Camera initialize */
    ofCamera camera;
    int camToView; // which camera index are we looking through
    int camToConfigure; // which camera index we are configuring
    vector<ofVec3f> points;
    //this keeps track of the center of all the points
    ofVec3f center;//center point of camera looking at
    ofLight spotlight;//spoltlight
    ofLight light;//light

    float mouseX,mouseY,mouseZ;//mouse position

    /* ofxSyphon initialize */
    ofTexture tex;
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    ofxSyphonClient mClient;
    ofxSyphonServerDirectory dir;
    int dirIdx;
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    /* Osc setup */
    ofxOscReceiver receiver;
    deque<string> messageBuffer;
    float xx,yy,zz; //position receiver
};
