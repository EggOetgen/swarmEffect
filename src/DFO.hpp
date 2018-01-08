//
//  DFO.hpp
//  DFO
//
//  Created by Edmund Oetgen on 12/10/2017.
//
//


/*THIS CLASS IS BASED ON THE JAVASCRIPT DFO IMPLEMENTATION BY MOHAMMA MAJID AL-RIFAIE WITH ADDED FEATURES AND FITNESS FUNCTION TO WORK WITH AUDI/*/
#pragma once


#include "ofMain.h"
#include "filterFly.hpp"

class DFO{
public:
    DFO();
    void setup(double dimensions_, int popSize_);
    void findNeighbors(int curr);
    double returnFeature(int f);
    float evaluate (vector<double> a, double target);
    void findBestFly();
    double filter(double input);
    
    double play();
    void getRandF_or_RingT_Neighbours(int curr, Boolean topology);
    void run(double target);
        void reset();

    
    double dimensions;
    int popSize;
    float dt; //disturbaance threshold
    
    int imgW, imgH;
    float width, height;
    vector<filterFly *> flies;
    int leftNeighbor;
    int rightNeighbor;
    int bestFlyIndex;
    
    
    float lowerFreqRange, upperFreqRange;

    
    
    
    double t;
    
};