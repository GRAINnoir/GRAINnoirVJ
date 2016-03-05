//
//  grainOSC.cpp

#include "grainOSC.h"

nanoOSC::nanoOSC(){};

void nanoOSC::setup(){
    receiver.setup(PORT);
    current_msg_string = 0;
}

void nanoOSC::update(){
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for message
        
        // faders
        if(m.getAddress().find("fader") == 5){
            faderCC = m.getAddress().substr(11, 2);
            for(int i=0; i<NUM_FADER;i++){
                if (faderCC == ofToString(i)) {
                    fader[i+1] = m.getArgAsFloat(0);
                }
                cout<<"fader["<<i+1<<"]: "<<fader[i+1]<<endl;
            }
        }
        // dials
        else if(m.getAddress().find("dial") == 5){
            dialCC = m.getAddress().substr(10, 2);
            for(int i=0; i<NUM_DIAL;i++){
                if (dialCC == ofToString(i+16)) {
                    dial[i+1] = m.getArgAsFloat(0);
                }
                cout<<"dial["<<i+1<<"]: "<<dial[i+1]<<endl;
            }
        }
        // btnTop
        else if(m.getAddress().find("top") == 12){
            btnTopCC = m.getAddress().substr(16, 2);
            for(int i=0; i<NUM_BTN_TOP;i++){
                if (btnTopCC == ofToString(i+32)) {
                    btnTop[i+1] = m.getArgAsInt(0);
                }
                cout<<"btnTop["<<i+1<<"]: "<<btnTop[i+1]<<endl;
            }
        }
        // btnMiddle
        else if(m.getAddress().find("middle") == 12){
            btnMiddleCC = m.getAddress().substr(19, 2);
            for(int i=0; i<NUM_BTN_MIDDLE;i++){
                if (btnMiddleCC == ofToString(i+48)) {
                    btnMiddle[i+1] = m.getArgAsInt(0);
                }
                cout<<"btnMiddle["<<i+1<<"]: "<<btnMiddle[i+1]<<endl;
            }
        }
        // btnBottom
        else if(m.getAddress().find("bottom") == 12){
            btnBottomCC = m.getAddress().substr(19, 2);
            for(int i=0; i<NUM_BTN_BOTTOM;i++){
                if (btnBottomCC == ofToString(i+64)) {
                    btnBottom[i+1] = m.getArgAsInt(0);
                }
                cout<<"btnBottom["<<i+1<<"]: "<<btnBottom[i+1]<<endl;
            }
        }
        // btnPrevTrack
        else if(m.getAddress().find("prevtrack") == 12){
            btnPrevTrack = m.getArgAsInt(0);
            cout<<"btnPrevTrack: "<<btnPrevTrack<<endl;
        }
        // btnNextTrack
        else if(m.getAddress().find("nexttrack") == 12){
            btnNextTrack = m.getArgAsInt(0);
            cout<<"btnNextTrack: "<<btnNextTrack<<endl;
        }
        // btnSet
        else if(m.getAddress().find("set") == 12){
            btnSet = m.getArgAsInt(0);
            cout<<"btnSet: "<<btnSet<<endl;
        }
        // btnPrevMarker
        else if(m.getAddress().find("prevmarker") == 12){
            btnPrevMarker = m.getArgAsInt(0);
            cout<<"btnPrevMarker: "<<btnPrevMarker<<endl;
        }
        // btnNextMarker
        else if(m.getAddress().find("nextmarker") == 12){
            btnNextMarker = m.getArgAsInt(0);
            cout<<"btnNextMarker: "<<btnNextMarker<<endl;
        }
        // btnCycle
        else if(m.getAddress().find("cycle") == 12){
            btnCycle = m.getArgAsInt(0);
            cout<<"btnCycle: "<<btnCycle<<endl;
        }
        // btnPrev
        else if(m.getAddress().find("prev") == 12){
            btnPrev = m.getArgAsInt(0);
            cout<<"btnPrev: "<<btnPrev<<endl;
        }
        // btnNext
        else if(m.getAddress().find("next") == 12){
            btnNext = m.getArgAsInt(0);
            cout<<"btnNext: "<<btnNext<<endl;
        }
        // btnStop
        else if(m.getAddress().find("stop") == 12){
            btnStop = m.getArgAsInt(0);
            cout<<"btnStop: "<<btnStop<<endl;
        }
        // btnPlay
        else if(m.getAddress().find("play") == 12){
            btnPlay = m.getArgAsInt(0);
            cout<<"btnPlay: "<<btnPlay<<endl;
        }
        // btnRecord
        else if(m.getAddress().find("record") == 12){
            btnRecord = m.getArgAsInt(0);
            cout<<"btnRecord: "<<btnRecord<<endl;
        }
        // input
        else if(m.getAddress().find("input") == 5){
            input = m.getArgAsInt(0);
            cout<<"input: "<<input<<endl;
        }
        // inputScale
        else if(m.getAddress().find("scale") == 5){
            inputScale = m.getArgAsFloat(0);
            cout<<"inputScale: "<<inputScale<<endl;
        }
        // FFT
        else if(m.getAddress().find("fft") == 5){
            fft = m.getArgAsFloat(0);
            cout<<"fft: "<<fft<<endl;
        }
        else{
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
        }
        
    }
    
}

nanoOSC::~nanoOSC(){};
