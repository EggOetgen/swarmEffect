#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
  
    /* This is stuff you always need.*/
    
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
    lAudioOut			= new float[initialBufferSize];/* outputs */
    rAudioOut			= new float[initialBufferSize];
    lAudioIn			= new float[initialBufferSize];/* inputs */
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
    ofSoundStreamSetup(2,2, this, sampleRate, initialBufferSize, 4);/* Call this last ! */
    
    dfo.setup(1, 10);
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
   
    if(peakFreq != 0)
        dfo.run(peakFreq);
   // cout <<peakFreq <<endl;
     cout << dfo.flies[dfo.bestFlyIndex]->fitness << " " << dfo.bestFlyIndex << " " <<peakFreq << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
//    float horizWidth = 500.;
//    float horizOffset = 100;
//    float fftTop = 250;
//    float mfccTop = 350;
//    float chromagramTop = 450;
//    
//    ofSetColor(255, 0, 0,255);
//    
//    //draw fft output
//    float xinc = horizWidth / fftSize * 2.0;
//    for(int i=0; i < fftSize / 2; i++) {
//        //magnitudesDB took out
//        float height = fft.magnitudes[i] * 100;
//        ofRect(horizOffset + (i*xinc),250 - height,2, height);
//    }
    
 
    gui.begin();
    {
    
        ImGui::SliderFloat("Dry/Wet", &dryWet, 0.0f, 1.0f);
        ImGui::SliderFloat("Disturbacne", &dfo.dt,0.001f, 0.1f);
        ImGui::SliderFloat("lower limit", &dfo.lowerFreqRange,  20.f, 20000.1f);
         ImGui::SliderFloat("upper limit", &dfo.upperFreqRange,  20.f, 20000.1f);  

      //  ImGui::SliderFloat("Gain", &gain, 0.0f, 1.0f);
    }
        gui.end();
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
        //magnitudesDB took out
        float height = fft.magnitudes[i] * 100;
        // cout<<height <<endl;
        ofRect(horizOffset + (i*xinc),250 - height,2, height);
    }
    
    float xinc2 = horizWidth / fftSize * 2.0;
    for(int i=0; i < fftSize / 2; i++) {
        //magnitudesDB took out
        float height = fftpost.magnitudes[i] ;
        // cout<<height <<endl;
        ofRect(horizOffset + (i*xinc2),550 - height,2, height);
    }

    ofPopStyle();

   // dfo.display();
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    
    
    for (int i = 0; i < bufferSize; i++){
        wave = lAudioIn[i];
       
        // thisGuy
        if( fft.process(wave)){
            //			int bins   = fftSize / 2.0;
            //do some manipulation
            //			int hpCutoff = floor(((mouseX + ofGetWindowPositionX()) / (float) ofGetScreenWidth()) * fftSize / 2.0);
            //highpass
            //			memset(mfft.magnitudes, 0, sizeof(float) * hpCutoff);
            //			memset(mfft.phases, 0, sizeof(float) * hpCutoff);
            //lowpass
            //			memset(mfft.magnitudes + hpCutoff, 0, sizeof(float) * (bins - hpCutoff));
            //			memset(mfft.phases + hpCutoff, 0, sizeof(float) * (bins - hpCutoff));
            fft.magsToDB();
            //			for(int z=0; z < 512; z++) cout << mfft.magnitudesDB[z] << ",";
            //			cout << "---------\n";
            //            oct.calculate(mfft.magnitudesDB);
            
            
            /* for (int j = 0; j < 12; j++) {
             chromagram[j] = 0;
             }
             int j = 0;
             for (int i = 0; i < oct.nAverages; i++) {
             chromagram[j] += oct.averages[i];
             j++;
             j = j % 12;
             } */
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
            //            centroid = sum / (fftSize / 2);
          //  double tempp
        peakFreq = (float)maxBin/fftSize * 44100;
//        if(tempPeakFreq !=0)
//            peakFreq = tempPeakFreq;
        
                 // if(wave<0.02) peakFreq = 0;
            
     //       mfcc.mfcc(fft.magnitudes, mfccs);
            //cout << mfft.spectralFlatness() << ", " << mfft.spectralCentroid() << endl;
        
        //inverse fft
        //        gettimeofday(&callTS,NULL);
        //        ifftVal = ifft.process(mfft.magnitudes, mfft.phases);
        //        gettimeofday(&callEndTS,NULL);
        //        callTime = (float)(callEndTS.tv_usec - callTS.tv_usec) / 1000000.0;
        //        callTime += (float)(callEndTS.tv_sec - callTS.tv_sec);
        //        //play result
        //  mymix.stereo(wave, outputs, 0.5);
        //float mix = ((mouseX + ofGetWindowPositionX()) / (float) ofGetScreenWidth());
        float mix = 0;
      //  double noise = osc.noise();
     //   if(wave>gate){
      
       // noise = dfo.filter(noise);//svf.setCutoff(200).setResonance(0).play(noise, 0, 1.0, 0,0);
//        double filtnoisel = filtl.lores(noise, 199, 0.01);
//         double filtnoiseh = filth.hires(noise, 201, 0.01);
        outputs[0] = outputs[1] =((dfo.filter(wave) * 0.01) * (1-dryWet))+ (wave * dryWet);
          //  outputs[0] = outputs[1] =dfo.play() * 0.002;
            if(fftpost.process(dfo.filter(wave))){
            
                fftpost.magsToDB();
            }
        //   mymix.stereo((wave * mix) + ((1.0-mix) * ifftVal), outputs, 0.5);
        lAudioOut[i] = output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
        rAudioOut[i] = output[i*nChannels + 1] = outputs[1];
        //        lAudioOut[i] = 0;
        //      rAudioOut[i] = 0;
        
        }
    
    }

    


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){

    
        for (int i = 0; i < bufferSize; i++){
//            
//            /* you can also grab the data out of the arrays*/
//            wave = lAudioIn[i];
//            if (fft.process(wave)) {
//                //			int bins   = fftSize / 2.0;
//                //do some manipulation
//                //			int hpCutoff = floor(((mouseX + ofGetWindowPositionX()) / (float) ofGetScreenWidth()) * fftSize / 2.0);
//                //highpass
//                //			memset(mfft.magnitudes, 0, sizeof(float) * hpCutoff);
//                //			memset(mfft.phases, 0, sizeof(float) * hpCutoff);
//                //lowpass
//                //			memset(mfft.magnitudes + hpCutoff, 0, sizeof(float) * (bins - hpCutoff));
//                //			memset(mfft.phases + hpCutoff, 0, sizeof(float) * (bins - hpCutoff));
//                fft.magsToDB();
//                //			for(int z=0; z < 512; z++) cout << mfft.magnitudesDB[z] << ",";
//                //			cout << "---------\n";
//                // oct.calculate(fft.magnitudesDB);
//                
//                
//                /* for (int j = 0; j < 12; j++) {
//                 chromagram[j] = 0;
//                 }
//                 int j = 0;
//                 for (int i = 0; i < oct.nAverages; i++) {
//                 chromagram[j] += oct.averages[i];
//                 j++;
//                 j = j % 12;
//                 } */
//                
//                sum = 0;
//               maxFreq = 0;
//                maxBin = 0;
//                
//                for (int i = 0; i < fftSize/2; i++) {
//                    sum += fft.magnitudes[i];
//                    if (fft.magnitudes[i] > maxFreq) {
//                        maxFreq2=fft.magnitudes[i];
//                        maxBin = i;
//                    }
//                }
////                centroid = sum / (fftSize / 2);
////                peakFreq = (float)maxBin/fftSize * 44100;
//                

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
