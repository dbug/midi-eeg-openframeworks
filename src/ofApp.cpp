#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //myThinkGear.setup("/dev/tty.MindWave", 9600);
    // setup thinkgear hardware using serial streamer or comms driver (osx only tested).
    // TG_STREAM_PARSER is default
    // blinks only work in TG_COMMS_DRIVER mode
    myThinkGear.setup("/dev/tty.MindWave", 57600, TG_STREAM_PARSER); //TG_STREAM_PARSER or TG_COMMS_DRIVER
    myThinkGear.addEventListener(this);
    
    midiOut.listPorts();
    midiOut.openPort(3);
    
    _timer = new ofxSimpleTimer();
    _timer->setTime(60, 2);
    _timer->setName("myTimer");
    _timer->start();
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &ofApp::timerCompelte);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    myThinkGear.update();
    _timer->update();
    
    _currentTime = _timer->getCurrentTime();
    _totalTime   = _timer->getTotalTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(caption(), 10, 20);
 }

string ofApp::caption()
{
    stringstream s;
    
    s << ofGetFrameRate() << endl;
    s << "count : " << _currentCount << " / " << _totalCount << endl;
    s << "time  : " << _currentTime << " / " << _totalTime << endl;
    s << "deltaInt  : " << deltaInt << endl;
    s << "thetaInt  : " << thetaInt << endl;
    s << "lowAlphaInt  : " << lowAlphaInt << endl;
    s << "highAlpha  : " << highAlpha << endl;
    s << "lowBeta  : " << lowBeta << endl;
    s << "highBeta  : " << highBeta << endl;
    s << "lowGamma  : " << lowGamma << endl;
    s << "highGamma  : " << highGamma << endl;
    return s.str();
}

//--------------------------------------------------------------
void ofApp::timerCompelte(string &name)
{
    _currentCount = _timer->getLoopCurrentCount();
    _totalCount   = _timer->getLoopTotalCount();
    
    if(name == "myTimer")
    {
        if(_currentCount == _totalCount)
        {
            cout << _currentCount << "/" << _totalCount << endl;
            cout << "[" << name << "] Complete" << endl;
            playNote();
             stopNote();
            _timer->start();
        }
        else
        {
           
            cout << _currentCount << "/" << _totalCount << endl;
        }
    }
    
}


void ofApp::playNote(){
    int deltaIntNOTE = ofMap(deltaInt, 0, 1500000, 0, 127);
    midiOut.sendNoteOn(1, deltaIntNOTE, 127);
    int thetaIntNOTE = ofMap(thetaInt, 0, 600000, 0, 127);
    midiOut.sendNoteOn(2, thetaIntNOTE, 127);
    int lowAlphaIntNote = ofMap(lowAlphaInt, 0, 75000, 0, 127);
    midiOut.sendNoteOn(3, lowAlphaIntNote, 127);
    
    int highAlphaNOTE = ofMap(highAlpha, 0, 150000, 0, 127);
    midiOut.sendNoteOn (4, highAlphaNOTE, 127);
    int lowBetaNOTE = ofMap(lowBeta, 0, 60000, 0, 127);
    midiOut.sendNoteOn(5, lowBetaNOTE, 127);
    int highBetaNOTE = ofMap(highBeta, 0, 60000, 0, 127);
    midiOut.sendNoteOn(6, highBetaNOTE, 127);
    
    int lowGammaNOTE = ofMap(lowGamma, 0, 30000, 0, 127);
    midiOut.sendNoteOn(7, lowGammaNOTE, 127);
    int highGammaNote = ofMap(highGamma, 0, 30000, 0, 127);
    midiOut.sendNoteOn(8, highGammaNote, 127);
    
    
        ofDrawBitmapString(caption(), 10, 20);
}

void ofApp::stopNote(){
     int deltaIntNOTE = ofMap(deltaInt, 0, 1500000, 0, 127);
    midiOut.sendNoteOff(1, deltaIntNOTE, 127);
    int thetaIntNOTE = ofMap(thetaInt, 0, 600000, 0, 127);
    midiOut.sendNoteOff(2, thetaIntNOTE, 127);
    int lowAlphaIntNote = ofMap(lowAlphaInt, 0, 75000, 0, 127);
    midiOut.sendNoteOff(3, lowAlphaIntNote, 127);
    
    
    int highAlphaNOTE = ofMap(highAlpha, 0, 150000, 0, 127);
    midiOut.sendNoteOff(4, highAlphaNOTE, 127);
    int lowBetaNOTE = ofMap(lowBeta, 0, 60000, 0, 127);
    midiOut.sendNoteOff(5, lowBetaNOTE, 127);
    int highBetaNOTE = ofMap(highBeta, 0, 60000, 0, 127);
    midiOut.sendNoteOff(6, highBetaNOTE, 127);
    
    int lowGammaNOTE = ofMap(lowGamma, 0, 30000, 0, 127);
    midiOut.sendNoteOff(7, lowGammaNOTE, 127);
    int highGammaNote = ofMap(highGamma, 0, 30000, 0, 127);
    midiOut.sendNoteOff(8, highGammaNote, 127);
    
    ofDrawBitmapString(caption(), 10, 20);
}


//--------------------------------------------------------------
// thinkgear events
void ofApp::onThinkgearReady(ofxThinkgearEventArgs& args){
    ofLog() << "*** THINKGEAR Ready...";
}

void ofApp::onThinkgearConnecting(ofxThinkgearEventArgs& args){
    ofLog() << "*** THINKGEAR connecting...";
}

void ofApp::onThinkgearError(ofMessage& err){
    ofLog() << "*** THINKGEAR onError..." << err.message;
}

// raw data does not send at frame rate - it sends faster! 512 samples a second
void ofApp::onThinkgearRaw(ofxThinkgearEventArgs& args){
   // ofLog() << "raw: " << args.raw;
}

// no visual indicator for blinks
void ofApp::onThinkgearBlinkStrength(ofxThinkgearEventArgs& args){
    // only works when using the comms driver (TG_COMMS_DRIVER)
    ofLog() << "blink: " << args.blinkStrength;
}


// battery never fires?
void ofApp::onThinkgearBattery(ofxThinkgearEventArgs& args){
    ofLog() << "*** THINKGEAR battery: " << args.battery;
}

void ofApp::onThinkgearPoorSignal(ofxThinkgearEventArgs& args){
    ofLog() << "poor signal: " << args.poorSignal;
}

void ofApp::onThinkgearAttention(ofxThinkgearEventArgs& args){
    ofLog() << "attention: " << args.attention;
}

void ofApp::onThinkgearMeditation(ofxThinkgearEventArgs& args){
    ofLog() << "meditation: " << args.meditation;
}

void ofApp::onThinkgearEeg(ofxThinkgearEventArgs& args){
    // about the 8 eeg bands (Comparison table of EEG rhythmic activity frequency bands): http://en.wikipedia.org/wiki/Electroencephalography
    // about neurusky's interpretation: http://support.neurosky.com/kb/development-2/eeg-band-power-values-units-amplitudes-and-meaning
    
    stringstream eegBands;
    eegBands << "delta: " << args.eegDelta;
    //delta.push_back(args.eegDelta);
    deltaInt = args.eegDelta;
    eegBands << "theta: " << args.eegTheta;
    thetaInt = args.eegTheta;
    
    eegBands << "alpha low: " << args.eegLowAlpha;
    lowAlphaInt= args.eegLowAlpha;
    
    eegBands << "alpha high: " << args.eegHighAlpha;
    highAlpha = args.eegHighAlpha;
    eegBands << "beta low: " << args.eegLowBeta;
    lowBeta = args.eegLowBeta;
    eegBands << "beta high: " << args.eegHighBeta;
    highBeta = args.eegHighBeta;
    eegBands << "gamma low: " << args.eegLowGamma;
    lowGamma = args.eegLowGamma;
    eegBands << "gamma high: " << args.eegHighGamma;
    highGamma = args.eegHighGamma;
    ofLog() << eegBands.str();
    //targetFrequency = args.eegDelta;
    //phaseAdderTarget = ((targetFrequency / (float) sampleRate) * TWO_PI)/500;
    //targetFrequency = args.eegTheta;
    //phaseAdderTarget = ((targetFrequency / (float) sampleRate) * TWO_PI)/500;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	midiOut.sendNoteOn(1, key, 1);
    switch (key)
    {
        case 's':
            _timer->start();// start
            break;
        case 'r':
            _timer->reset();// reset
            break;
        case 'p':
            _timer->pause();// pause
            break;
        case 'd':
            
            if(DEBUG)
            {
                _timer->debugStart();
            }
            else
            {
                _timer->debugStop();
            }
            DEBUG = !DEBUG;
            
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	midiOut.sendNoteOff(1, key, 0);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bNoise = true;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
 bNoise = false;
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
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
   // pan = 0.5f;
    ///float leftScale = 1 - pan;
   // float rightScale = pan;
    
    // sin (n) seems to have trouble when n is very large, so we
    // keep phase in the range of 0-TWO_PI like this:
   // while (phase > TWO_PI){
   //     phase -= TWO_PI;
  //  }
    
  //  if ( bNoise == true){
        // ---------------------- noise --------------
   //     for (int i = 0; i < bufferSize; i++){
    //        lAudio[i] = output[i*nChannels    ] = ofRandom(0, 1) * volume * leftScale;
    ///        rAudio[i] = output[i*nChannels + 1] = ofRandom(0, 1) * volume * rightScale;
    //    }
   // } else {
    //    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    //    for (int i = 0; i < bufferSize; i++){
     //       phase += phaseAdder;
     //       float sample = sin(phase);
      //      lAudio[i] = output[i*nChannels    ] = sample * volume * leftScale;
     //       rAudio[i] = output[i*nChannels + 1] = sample * volume * rightScale;
      //  }
}
