//
//  audio.h

#pragma once

#include "ofMain.h"

#define VOL_HISTORY_SIZE 400

class audio : public ofBaseApp{
    
public:
    
    audio();
    ~audio();
    
    void setup();
    void update();
    
    void audioIn(float * input, int bufferSize, int nChannels);
    void drawLeftChannel(int x, int y, int length = 2, int lineWidth = 3);
    void drawRightChannel(int x, int y, int length = 2, int lineWidth = 3);
    void drawAvrg(int x, int y, int length = 2, int lineWidth = 3);
    void drawGraph(int x, int y, int length, int graphScale = 100);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int bufferSize;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
     
};
