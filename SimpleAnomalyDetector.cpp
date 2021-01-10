#include <map>
#include "SimpleAnomalyDetector.h"
#include <string>
SimpleAnomalyDetector::SimpleAnomalyDetector(float threshold) {
    this->threshold = threshold;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() { }

float SimpleAnomalyDetector::cirCorr(correlatedFeatures cf, Point** points, int size) { }

bool SimpleAnomalyDetector::isAnomal(correlatedFeatures cf, Point *point){
    float correlation = dev(*point, cf.lin_reg);
    if (correlation > cf.threshold)
        return true;
    return false;
}

// learns the tendency of a given time series.
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    correlatedFeatures temp;
    float maxCorr = 0;
    float* sFlotIn = 0;
    int size = 0;
    bool isCorrelation = false;
    Point *ps[200];
    for (auto outItr = ts.table.begin(); outItr != ts.table.end(); ++outItr) { // Loop through the map.
        float* floOut = new float[outItr->second.size()];
        for (int i = 0; i < outItr->second.size(); floOut[i] = outItr->second[i], i++); // Turns the strings to float.
        for (auto inItr = ts.table.begin(); inItr != ts.table.end(); ++inItr) { // Loop through the map.
            size = outItr->second.size();
            float* floIn = new float[outItr->second.size()];
            for (int i = 0; i < outItr->second.size(); floIn[i] = inItr->second[i], i++); // Turns strings to float.
            if (outItr == inItr)
                continue;
            int flagInCf = 0; // Flag that carry the fact if the current correlation is already in cf vector.
            for (int cfI = 0; cfI < this->cf.size(); cfI++) {
                if (outItr->first == this->cf[cfI].feature2)
                    flagInCf = 1;
            }
            if (flagInCf == 1)
                continue;
            // Case the current correlation is the maximum so far.
            if (pearson(floOut, floIn, inItr->second.size()) > maxCorr) {
                maxCorr = pearson(floOut, floIn, inItr->second.size());
                temp.feature1 = outItr->first;
                temp.feature2 = inItr->first;
                temp.corrlation = maxCorr;
                //Point *ps[outItr->second.size()];
                float maxDev = 0;
                for (int k = 0; k < outItr->second.size(); k++){
                    ps[k] = new Point(outItr->second[k], inItr->second[k]); // Turns each local correlation to point.
                }
                temp.lin_reg = linear_reg(ps, outItr->second.size());
                for (int k = 0; k < outItr->second.size(); k++) {
                    if (maxDev < abs(dev(*ps[k], temp.lin_reg))) // case the current deviation is max deviation.
                        maxDev = abs(dev(*ps[k], temp.lin_reg));
                }
                temp.threshold = maxDev*1.1; // ten present higher for little deviation.
                //isCorrelation = true;
                sFlotIn = floIn;
            }
        }
        if (maxCorr>threshold)
            this->cf.push_back(temp);
        else if (maxCorr > 0.5 && maxCorr < threshold)
            cirCorr(temp, ps, size);
        //isCorrelation = false;
        maxCorr = 0;
    }

}

// Detects whether a anomaly occur.
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> vector;

    for (int j = 0; j < ts.table.begin()->second.size(); ++j) { // Loop through the map.
        int iter = -1;
        for (auto i = cf.begin(); i != cf.end(); ++i) { // Loop through the cf vector.
            iter++;
            float floatA = ts.table.at(i->feature1)[j];
            float floatB = ts.table.at(i->feature2)[j];
            auto *p = new Point(floatA, floatB); // A point represent the two current features.

            //float correlation = dev(*p, i->lin_reg);
            // Case the correlation is bigger then the threshold determined by the current correlation deviation.
            if (isAnomal(*i, p)) {
                const string description = i->feature1 + "-" + i->feature2;
                const long timeStep = j + 1; // For time step to start with 1 instead of 0.
                AnomalyReport ar(description, timeStep); // Build a anomaly report with those features.
                vector.push_back(ar);
            }
        }
    }
    return (vector);
}