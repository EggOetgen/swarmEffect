#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "fly.hpp"
#include "DFO.hpp"
#include "ofxImGui.h"

/*BE CAREFUL WITH THIS AS CAN FEEDBACK*/

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
      float torus(float input);
  
    //standard max stuff
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);

    float 	* lAudioOut; /* outputs */
    float   * rAudioOut;
    
    float * lAudioIn; /* inputs */
    float * rAudioIn;
    
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    

    
    /*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
    double wave,sample,outputs[2], ifftVal;
    maxiMix mymix;
    maxiOsc osc;

    maxiOsc noise;
    maxiFilter filtl, filth;
    maxiSVF svf;
    
    ofxMaxiFFT fft, fftpost;
    int fftSize;
    int bins, dataSize;
		
    float dryWet;
    float peakFreq = 0;
    float centroid = 0;
    float maxFreq2;
    
    float sum = 0;
    float maxFreq = 0;
    int maxBin = 0;
    float gate = 0;
       
    DFO dfo;
    ofxImGui::Gui gui;
};

/*BE CAREFUL WITH THIS AS CAN FEEDBACK*/