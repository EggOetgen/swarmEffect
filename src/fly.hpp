//
//  fly.hpp
//  DFO
//
//  Created by Edmund Oetgen on 10/10/2017.
//
//

#pragma once


#include "ofMain.h"


class fly{
public:
    fly(double dimensions, float w);
   // void init(double dimensions, float w);
    vector<double> returnFeatureVector();
    void setFeatureVector(vector<double> newFeatVec);
    double getFeature(int f);
    double getDistanceSquared(vector<double> featVec2);
    void setFitness(double t);
    double getFitness();
    
    vector<double> featVec;
    double fitness;
    
    
    
};