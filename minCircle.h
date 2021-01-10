// 20554331

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include "vector"
#include "cmath"
#include "anomaly_detection_util.h"

using namespace std;

// ------------ DO NOT CHANGE -----------

class Circle {
public:
    Point center;
    float radius;

    Circle(Point c, float r) : center(c), radius(r) {}


};
Circle getCircleFromThreePoints(Point a, Point b, Point c);
Circle getCircleFromTwoPoints(Point a, Point b);
bool isPointInCircle(Point p, Circle c);
Circle findMinCircleRec(Point **points, int n, vector<Point *> newPoints);
Circle findMinCircle(Point **points, size_t size);

// --------------------------------------


#endif /* MINCIRCLE_H_ */