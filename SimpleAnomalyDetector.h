

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
//#define THRESHOLD 0.9

struct correlatedFeatures{
    bool isCircle=0;
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold=0.9;
    float centerX;
    float centerY;
    float rad;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
    vector<correlatedFeatures> cf;
    float threshold;
public:
    SimpleAnomalyDetector(float threshold);
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);

    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

    virtual float cirCorr(correlatedFeatures cf, Point** points, int size);



    virtual bool isAnomal(correlatedFeatures cf, Point *point);

    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }



};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
