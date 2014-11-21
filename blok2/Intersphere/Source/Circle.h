//
//  Circle.h
//  Intersphere


#ifndef __Intersphere__Circle__
#define __Intersphere__Circle__

#include <iostream>
#include <vector>

using namespace std;

class Circle
{
public:
    Circle(float inX, float inY, int inID, vector<Circle> othersIn);
    void location();
    void draw();
    void collision();
    void circleID();
    
private:
    float x;
    float y;
    float r;
    int ID;
    vector<Circle> others;
    
};


#endif /* defined(__Intersphere__Circle__) */
