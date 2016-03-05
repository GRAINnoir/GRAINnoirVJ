#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
#ifdef __APPLE__
    //CGDisplayHideCursor(NULL);
#endif
    
    ofBackground(backColor);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetSmoothLighting(true);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofHideCursor();
    
    // OSC
    osc.setup();
    
    // AUDIO
    audio.setup();
    osc.input = true;
    osc.inputScale = 1;
    
    // COLOR
    backColor = 0;
    backAlpha = 255;
    strokeColor = 255;
    strokeAlpha = 255;
    redChannel = 0;
    greenChannel = 0;
    blueChannel = 0;
    audioColor = 0;
    invertColor = false;
    
    // CAMERA
    camDistance = 2000;
    cam.setFarClip(10000);
    
    // LIGHT
    ambient.setPosition(0, 0, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    // OSC
    osc.update();
    
    // AUDIO
    audio.update();
    if (!osc.input) osc.inputScale = 0;
    else osc.inputScale = osc.inputScale;
    
    vol = audio.scaledVol*osc.inputScale;
    
    // COLOR
    
    // BLACK & WHITE
    if (osc.btnCycle == 0) {
        invertColor = false;

    } else if (osc.btnCycle == 1) {
        invertColor = true;
    }
    
    if (invertColor) {
        backColor = 255;
        strokeColor = 0;
    }
    
    if (!invertColor) {
        backColor = 0;
        strokeColor = 255;
    }
    
    audioColor = ofMap(vol, 0., 1.,0,255);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(backColor);
    ofSetColor(strokeColor);
    
    audio.drawAvrg(0, ofGetHeight()/2, ofGetWidth()/audio.bufferSize+1, ofMap(vol, 0., 1.,1,10));
    audio.drawGraph(0, 400, 5, ofMap(vol, 0., 1.,100,400));
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            audio.soundStream.start();
            break;
        case 'm':
            audio.soundStream.stop();
            break;
        default:
            break;
    }
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
