//
//  grainOSC.h

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 8888
#define NUM_MSG_STRINGS 20

#define NUM_FADER 8
#define NUM_DIAL 8
#define NUM_BTN_TOP 8
#define NUM_BTN_MIDDLE 8
#define NUM_BTN_BOTTOM 8

class nanoOSC{
    
    public:
        nanoOSC();
    
        void setup();
        void update();
    
        ofxOscReceiver receiver;
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        float fader[NUM_FADER];
        float dial[NUM_DIAL];
        int btnTop[NUM_BTN_TOP];
        int btnMiddle[NUM_BTN_MIDDLE];
        int btnBottom[NUM_BTN_BOTTOM];
        int btnPrevTrack;
        int btnNextTrack;
        int btnSet;
        int btnPrevMarker;
        int btnNextMarker;
        int btnCycle;
        int btnPrev;
        int btnNext;
        int btnStop;
        int btnPlay;
        int btnRecord;
    
        string faderCC;
        string dialCC;
        string btnTopCC;
        string btnMiddleCC;
        string btnBottomCC;
    
        bool input;
        float inputScale;
        float fft;
    
        ~nanoOSC();
    
    private:
    
    
};