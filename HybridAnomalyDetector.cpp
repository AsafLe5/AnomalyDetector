
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector(float threshold):SimpleAnomalyDetector(threshold) {
	// TODO Auto-generated constructor stub
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

float HybridAnomalyDetector::cirCorr(correlatedFeatures cf, Point** points, int size) {
    Circle circle = findMinCircle(points, size);
    cf.centerX = circle.center.x;
    cf.centerY = circle.center.y;
    cf.rad = circle.radius;
    cf.threshold = cf.rad * 1.1; //אפשרי שגם את זה צריך לשנות
    cf.isCircle = true;
    this->cf.push_back(cf);
}

bool HybridAnomalyDetector::isAnomal(correlatedFeatures cf, Point *point){

    if (!cf.isCircle){
        return SimpleAnomalyDetector::isAnomal(cf, point);
    }

    else{
        float cor = sqrt(pow(point->x - cf.centerX, 2) + pow(point->y - cf.centerY, 2));
        if (cor > cf.threshold)
            return true;
    }
    return false;
}
