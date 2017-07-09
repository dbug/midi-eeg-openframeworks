#pragma once

#include "ofMain.h"
#include "ofxThinkgear.h"
#include "ofxMidi.h"
#include "ofxSimpleTimer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        ofxThinkgear myThinkGear;
    	ofxMidiOut midiOut;
    
    ofxThinkgearEventArgs data;
    string deviceName;
    int deviceBaudRate;
    
    void onThinkgearError(ofMessage& err);
    void onThinkgearReady(ofxThinkgearEventArgs& args);
    void onThinkgearRaw(ofxThinkgearEventArgs& args);
    void onThinkgearBattery(ofxThinkgearEventArgs& args);
    void onThinkgearPoorSignal(ofxThinkgearEventArgs& args);
    void onThinkgearBlinkStrength(ofxThinkgearEventArgs& args);
    void onThinkgearAttention(ofxThinkgearEventArgs& args);
    void onThinkgearMeditation(ofxThinkgearEventArgs& args);
    void onThinkgearEeg(ofxThinkgearEventArgs& args);
    void onThinkgearConnecting(ofxThinkgearEventArgs& args);
    void audioOut(float * input, int bufferSize, int nChannels);
    void playNote();
    void stopNote();
    
    ofSoundStream soundStream;
    ofSoundStream thetaSoundStream;
    
    float 	pan;
    int		sampleRate;
    bool 	bNoise;
    float 	volume;
    
    vector <float> lAudio;
    vector <float> rAudio;
    
    //------------------- for the simple sine wave synthesis
    float 	targetFrequency;
    float 	phase;
    float 	phaseAdder;
    float 	phaseAdderTarget;

    int deltaInt;
    int thetaInt;
    int lowAlphaInt;
    int highAlpha;
    int lowBeta;
    int highBeta;
    int lowGamma;
    int highGamma;
    
    string caption();
    
    ofxSimpleTimer *_timer;
    
    void timerCompelte(string & name);
    
    bool DEBUG = false;
    int _currentCount;
    int _totalCount;
    int _currentTime;
    int _totalTime;
    

};
