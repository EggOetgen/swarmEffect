

#pragma once
#include "fly.hpp"
#include "ofxMaxim.h"

class filterFly: public fly{
    
    
public:
    filterFly(double dimensions, float w,  float lowerFreqRange, float upperFreqRange);
    double buzz(double input);
    double newBuzz();
    void setPitch(float lowerFreqRange, float upperFreqRange);
    
    maxiSVF filter;
    maxiOsc osc;
    double cutoff;
    double resonance;
    double gain;
    
    
};