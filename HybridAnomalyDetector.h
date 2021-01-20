

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector(float threshold);
	virtual ~HybridAnomalyDetector();

	virtual float cirCorr(correlatedFeatures cf, Point** points, int size);

    virtual bool isAnomal(correlatedFeatures cf, Point *point);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
