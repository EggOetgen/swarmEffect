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
    
    scaleF = 5;
    //    dimensions = dimensions_;
    //    popSize = popSize_;
    dt = 0.01;
    
    
    evalCount = 0;
    FE_allowed = 30000;
    offset = -0.0;
    
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
       // flies[i]->init(dimensions, imgW);
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
    
    // println( leftN + " :: " + rightN );
    
}

float DFO::evaluate(vector<double> a, double target) {
    evalCount++;
    double curFreq = a[0];
    double fitness = 0;
    if (curFreq > target)
        fitness = remainder(curFreq, target);
    else
        fitness = remainder(target, curFreq);

    return abs( target - a[0] );
    // Sphere Schwefel12 Rosenbrock GSchwefel26
    // Rastrigin Ackley Griewank PenalizedP8 PenalizedP16
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
    
       if (evalCount < FE_allowed) {
        // EVALUATION Phase
        for (int i = 0; i < popSize; i++)
        {
            flies[i]->setFitness(evaluate(flies[i]->returnFeatureVector(), target));
            
        }
        
        findBestFly();
           flies[bestFlyIndex]->fitness;
        // INTERACTION Phase
        for (int i = 0; i < popSize; i++) {
            
            //  findNeighbors(i);
            getRandF_or_RingT_Neighbours(i, true);
            double leftP, rightP;
            
            leftP = flies[leftNeighbor]->getFitness();// leftD *
            // fly[leftN].getFitness();
            rightP = flies[rightNeighbor]->getFitness();// rightD *
            // fly[rightN].getFitness();
            
            
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
}

double DFO::filter(double input){
    
    
    double output = 0;
    for (int i = 0; i < flies.size(); i++){
       // flies[i]->setFitness(evaluate(flies[i]->returnFeatureVector(), t));
      // if (flies[i]->fitness < 500)
        output += (flies[i]->buzz(input) ) ;
    
    }
    return output;

}

double DFO::play(){
    
    
    double output = 0;
    for (int i = 0; i < flies.size(); i++){
        // flies[i]->setFitness(evaluate(flies[i]->returnFeatureVector(), t));
         //if (flies[i]->fitness < 50)
        output += (flies[i]->newBuzz() ) ;
        
    }
    return output;
    
}


double DFO::Sphere(vector<double> p) {
    double a = 0;
    for (int i = 0; i < dimensions; i++) {
        a = a + pow(p[i] + offset, 2);
    }
    
    return a;
}

void DFO::display(){
    ofPushStyle();
    // Draw the flies and update their positions
    for (int i = 0; i < popSize; i++) {
        ofSetColor(255, 255, 255);
        
        
        if (true) {
            ofSetColor(200, 200, 200, 5);
            ofSetLineWidth((float) 10.5);
            ofLine(width / 2, 0, width / 2, height); // y
            ofPushMatrix();
            ofTranslate(imgW * scaleF / 2, imgH * scaleF / 2);
            
            int gap = height / (dimensions + 1);
            for (int d = 0; d < dimensions; d++) {
                ofSetColor(0, 0, 0, 100);
                ofSetLineWidth((float) 0.3);
                // Horizontal Lines
                int xGap = imgW * scaleF / 2;
                int yGap = -imgW * scaleF / 2 + gap * (d + 1);
                
                ofLine(-xGap, yGap, xGap, yGap);
                
                // flies position
                int eSize = 5;
                if (i == bestFlyIndex) {
                    ofSetColor(255, 0, 0);
                    eSize = eSize * 2;// 5;
                }else{
                    ofSetColor(0);
                }
                ofDrawEllipse((float) flies[i]->getFeature(d) * scaleF / 2, yGap, eSize, eSize);
                
                // }
            }
            
            ofPopMatrix();
            
        }
        
    }
    ofPopStyle();
    
}

void DFO::reset(){

    setup(dimensions, popSize);

}
