//
//  DFO.hpp
//  DFO
//
//  Created by Edmund Oetgen on 12/10/2017.
//
//

#pragma once


#include "ofMain.h"
#include "filterFly.hpp"

class DFO{
public:
    DFO();
    void setup(double dimensions_, int popSize_);
    // void init(double dimensions, int popSize);
    void findNeighbors(int curr);
    double returnFeature(int f);
    float evaluate (vector<double> a, double target);
    void findBestFly();
    double filter(double input);
    
    double play();
    void getRandF_or_RingT_Neighbours(int curr, Boolean topology);
    void run(double target);
    void display();
    void reset();

    double Sphere(vector<double> p);
    
    double dimensions;
    int popSize;
    float dt; //disturbaance threshold
    
    int imgW, imgH;
    float width, height;
    int scaleF;
    
    vector<filterFly *> flies;
    int leftNeighbor;
    int rightNeighbor;
    int bestFlyIndex;
    
    
    float lowerFreqRange, upperFreqRange;

    
    int evalCount;
    int FE_allowed;
    double offset;
    
    double t;
    
};