//
//  audio.cpp

#include "audio.h"

audio::audio() {
    
}

//--------------------------------------------------------------
void audio::setup(){
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    //soundStream.printDeviceList();
    
    //soundStream.setDeviceID(0);
    
    bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(VOL_HISTORY_SIZE, 0.0);

    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void audio::update(){
    
    // scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    // record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= VOL_HISTORY_SIZE ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
}
//--------------------------------------------------------------
void audio::drawLeftChannel(int x, int y, int length, int lineWidth){

    ofPushStyle();
    ofPushMatrix();
    
    ofNoFill();
    ofSetLineWidth(lineWidth);
    
    ofBeginShape();
    for (unsigned int i = 0; i < left.size(); i++){
        ofVertex(x+i*length, y -left[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();

}
//--------------------------------------------------------------
void audio::drawRightChannel(int x, int y, int length, int lineWidth){
    
    ofPushStyle();
    ofPushMatrix();
    
    ofNoFill();
    ofSetLineWidth(lineWidth);
    
    ofBeginShape();
    for (unsigned int i = 0; i < right.size(); i++){
        ofVertex(x+i*length, y -right[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
}
//--------------------------------------------------------------
void audio::drawAvrg(int x, int y, int length, int lineWidth){
    
    ofPushStyle();
    ofPushMatrix();
    
    ofNoFill();
    ofSetLineWidth(lineWidth);
    
    ofBeginShape();
    for (unsigned int i = 0; i < left.size() + right.size(); i++){
        ofVertex(x+i*length, y -(left[i]*180.0f + right[i]*180.0f));
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
}
//--------------------------------------------------------------
void audio::drawGraph(int x, int y, int length, int graphScale){
    
    // draw the average volume:
    ofPushStyle();
    ofPushMatrix();
    
    ofNoFill();
    
    //lets draw the volume history as a graph
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory.size(); i++){
        //if( i == 0 ) ofVertex(i, VOL_HISTORY_SIZE);
        
        ofVertex(x+i*length, y - volHistory[i] * graphScale);
        
        //if( i == volHistory.size() -1 ) ofVertex(i, VOL_HISTORY_SIZE);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
}
//--------------------------------------------------------------
void audio::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    // lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    // this is how we get the mean of rms
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms
    curVol = sqrt(curVol);
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
}
//--------------------------------------------------------------
audio::~audio(){
    
}