#include "ofApp.h"

/*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
//--------------------------------------------------------------
void ofApp::setup(){
    
    /*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
  
    /* STANDARD MAX STUFF   */
    
    sampleRate 			= 44100;
    initialBufferSize	= 512;

    lAudioOut			= new float[initialBufferSize];
    rAudioOut			= new float[initialBufferSize];
    lAudioIn			= new float[initialBufferSize];
    rAudioIn			= new float[initialBufferSize];
    
    
    /* This is a nice safe piece of code */
    memset(lAudioOut, 0, initialBufferSize * sizeof(float));
    memset(rAudioOut, 0, initialBufferSize * sizeof(float));
    
    memset(lAudioIn, 0, initialBufferSize * sizeof(float));
    memset(rAudioIn, 0, initialBufferSize * sizeof(float));
    
    fftSize = 1024;
    fft.setup(fftSize, 512, 256);
    fftpost.setup(fftSize, 512, 256);



    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    ofSoundStreamSetup(2,2, this, sampleRate, initialBufferSize, 4);
    
    //our DFO has a search space of 1 and a population of 10
    dfo.setup(1, 10);
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
   
    //check we have an input signal!
    if(peakFreq != 0)
        dfo.run(peakFreq);
   
   }

//--------------------------------------------------------------
void ofApp::draw(){

    
    /*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
    gui.begin();
    {
    
        //mix of each signal
        ImGui::SliderFloat("Dry/Wet", &dryWet, 0.0f, 1.0f);
        //how likely 'flies' are to randomly reassign
        ImGui::SliderFloat("Disturbacne", &dfo.dt,0.001f, 0.1f);
        
        // the frequency range we want our flies to search
        ImGui::SliderFloat("lower limit", &dfo.lowerFreqRange,  20.f, 20000.1f);
         ImGui::SliderFloat("upper limit", &dfo.upperFreqRange,  20.f, 20000.1f);  

     
    }
        gui.end();
    
    //this bit taken from mick's maximillian examples, just so we can see what's goin on, top is input, bottom is output
    float horizWidth = 500.;
    float horizOffset = 100;
    float fftTop = 250;
    float mfccTop = 350;
    float chromagramTop = 450;
    ofPushStyle();
    ofSetColor(255, 0, 0,255);
    
    //    //draw fft output
    float xinc = horizWidth / fftSize * 2.0;
    for(int i=0; i < fftSize / 2; i++) {
            float height = fft.magnitudes[i] * 100;
    
        ofRect(horizOffset + (i*xinc),250 - height,2, height);
    }
    
    float xinc2 = horizWidth / fftSize * 2.0;
    for(int i=0; i < fftSize / 2; i++) {
               float height = fftpost.magnitudes[i] ;
 
        ofRect(horizOffset + (i*xinc2),550 - height,2, height);
    }

    ofPopStyle();

}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    /*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
    
    
    for (int i = 0; i < bufferSize; i++){
        wave = lAudioIn[i];
       
        //take our input signal, perform fft and find frequency with most energy, again taken from Mick's example
     
        if( fft.process(wave)){
            fft.magsToDB();
      
    }
             sum = 0;
            maxFreq = 0;
             maxBin = 0;
            
            for (int i = 0; i < fftSize/2; i++) {
                sum += fft.magnitudes[i];
                if (fft.magnitudes[i] > maxFreq) {
                    maxFreq=fft.magnitudes[i];
                    maxBin = i;
                }
            }
        
        peakFreq = (float)maxBin/fftSize * 44100;

        float mix = 0;
        //output mix of input as well as output from dfo
        //DFO is randomly assigning 'flies' a frequency, the closer this frequency to being harmonically relative to the peak frequency the fitter that fly, and the more it will attract others. Each fly filters the signal at their frequency.
          outputs[0] = outputs[1] =((dfo.filter(wave) * 0.01) * (1-dryWet))+ (wave * dryWet);
                     if(fftpost.process(dfo.filter(wave))){
            
                fftpost.magsToDB();
            }
                lAudioOut[i] = output[i*nChannels    ] = outputs[0];        rAudioOut[i] = output[i*nChannels + 1] = outputs[1];
     
        
        }
    
    }

/*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
    


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    /*BE CAREFUL WITH THIS AS CAN FEEDBACK*/
    
        for (int i = 0; i < bufferSize; i++){

            lAudioIn[i] = input[i*2];
            rAudioIn[i] = input[i*2+1];
            
            sum += input[i*2] * input[i*2];
            
        }

        
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
