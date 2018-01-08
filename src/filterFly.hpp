

#pragma once
#include "fly.hpp"
#include "ofxMaxim.h"

/*THIS CLASS IS BASED ON THE JAVASCRIPT DFO IMPLEMENTATION BY MOHAMMA MAJID AL-RIFAIE WITH ADDED FEATURES AND FITNESS FUNCTION TO WORK WITH AUDI/*/

//basically the same as parent, jsut with a big ol' state variable filter on it
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