//
//  DFO.cpp
//  DFO
//
//  Created by Edmund Oetgen on 12/10/2017.
//
//

#include "DFO.hpp"

DFO::DFO(){
    
    width = ofGetWidth();
    height = ofGetHeight();
    
           dt = 0.01;
    
       bestFlyIndex = 0;
    lowerFreqRange = 20;
    upperFreqRange = 6000;

}

void DFO::setup(double dimensions_, int popSize_){
    dimensions = dimensions_;
      imgW = 6000;
    imgH =  dimensions;
    popSize = popSize_;
    flies.clear();
    flies.resize(popSize);
    for (int i = 0; i < flies.size(); i++ ){
        flies[i] = new filterFly(dimensions, imgW, lowerFreqRange, upperFreqRange);

    }
}

//taken from Mohammad Majid al-Rifaie's example code in java
void DFO::findNeighbors(int curr){
    double minDL = 10E15;
    for (int i = 0; i < popSize; i++) {
        if (i == curr)
            continue;
        
        double d = flies[curr]->getDistanceSquared(flies[i]->returnFeatureVector());
        if (d < minDL) {
            minDL = d;
            leftNeighbor = i;
        }
    }
    
    double minDR = 10E15;
    for (int i = 0; i < popSize; i++) {
        if (i == curr)
            continue;
        if (i == leftNeighbor)
            continue;
        
        double d = flies[curr]->getDistanceSquared(flies[i]->returnFeatureVector());
        if (d < minDR) {
            minDR = d;
            rightNeighbor = i;
        }
    }
 
    
}

//fitness function. Divide current freq by ttarget. the lowere the remainder the more harmonically related
float DFO::evaluate(vector<double> a, double target) {
   
    double curFreq = a[0];
    double fitness = 0;
    if (curFreq > target)
        fitness = remainder(curFreq, target);
    else
        fitness = remainder(target, curFreq);

    return abs( target - a[0] );
    
}

void DFO::findBestFly() {
    double min = 10E10;
    
    for (int i = 0; i < popSize; i++) {
        if (flies[i]->getFitness() < min) {
            min = flies[i]->getFitness();
            bestFlyIndex = i;
        }
    }
}

void DFO::getRandF_or_RingT_Neighbours(int curr, Boolean topology) {
    
    if (topology) // RING
    {
        leftNeighbor = curr - 1;
        rightNeighbor = curr + 1;
        
        if (curr == 0)
            leftNeighbor = popSize - 1;
        if (curr == popSize - 1)
            rightNeighbor = 0;
    }
}


void DFO::run(double target){
    t = target;
    
              // EVALUATION Phase
        for (int i = 0; i < popSize; i++)
        {
            flies[i]->setFitness(evaluate(flies[i]->returnFeatureVector(), target));
            
        }
        
        findBestFly();
           flies[bestFlyIndex]->fitness;
        // INTERACTION Phase
        for (int i = 0; i < popSize; i++) {
            
                        getRandF_or_RingT_Neighbours(i, true);
            double leftP, rightP;
            
            leftP = flies[leftNeighbor]->getFitness();
            rightP = flies[rightNeighbor]->getFitness();
            
            int chosen;
            if (leftP < rightP)
                chosen = leftNeighbor;
            else
                chosen = rightNeighbor;
            int dCounter = 0;
            vector<double> temp;
            temp.resize(dimensions);
            
            for (int d = 0; d < dimensions; d++) {
                temp[d] = flies[i]->getFeature(d) + ofRandom(1.0) *  (flies[chosen]->getFeature(d) - flies[i]->getFeature(d));// FINAL
                
                
                
                    if (ofRandom(1.0) < dt)
                    {
                        temp[0]=  ofRandom(lowerFreqRange, upperFreqRange);
                       
                    }
            }
            
            if (temp[0]< lowerFreqRange ||temp[0] > upperFreqRange) {
              temp[0] =  ofRandom(lowerFreqRange, upperFreqRange);
                

                     }
            flies[i]->setFeatureVector(temp);
            
        }
        
    
}

//feed the input signal to the flys, they'll eat away with their filters
double DFO::filter(double input){
    
    
    double output = 0;
    for (int i = 0; i < flies.size(); i++){
              output += (flies[i]->buzz(input) ) ;
    
    }
    return output;

}

double DFO::play(){
    
    
    double output = 0;
    for (int i = 0; i < flies.size(); i++){
        
        output += (flies[i]->newBuzz() ) ;
        
    }
    return output;
    
}




void DFO::reset(){

    setup(dimensions, popSize);

}
