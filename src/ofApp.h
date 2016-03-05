#pragma once

#include "ofMain.h"
#include "grainOSC.h"
#include "audio.h"

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
    
    // OSC
    nanoOSC osc;
    
    // AUDIO
    audio audio;
    float vol;
    
    // COLOR
    float backColor;
    int backAlpha;
    int strokeColor;
    int strokeAlpha;
    int redChannel;
    int greenChannel;
    int blueChannel;
    int audioColor;
    bool invertColor;
    
    // CAMERA
    ofEasyCam cam;
    float camDistance;
    
    // LIGHT
    ofLight ambient;
    
};
