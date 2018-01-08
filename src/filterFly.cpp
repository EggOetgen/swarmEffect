//
//  filterFly.cpp
//  swarmEffect
//
//  Created by Edmund Oetgen on 23/11/

#include "filterFly.hpp"

filterFly::filterFly(double dimensions, float w,float lowerFreqRange, float upperFreqRange):fly(dimensions,w){

    setPitch( lowerFreqRange, upperFreqRange);
    cutoff = 200;
    resonance = 0.01;

}

void filterFly::setPitch(  float lowerFreqRange, float upperFreqRange){

    featVec[0] = ofRandom(  lowerFreqRange, upperFreqRange);
}

double filterFly::buzz(double input){

    double output = 0;
    filter.setCutoff(featVec[0]);
    filter.setResonance(0);
   // svf.setCutoff(200).setResonance(0).play(noise, 0, 1.0, 0,0);
    output = filter.play(input,  0, 1.0, 0,0);    
    return output;
}

double filterFly::newBuzz(){
    double output = 0;

   output =  osc.sawn(featVec[0]);
    return output;
}