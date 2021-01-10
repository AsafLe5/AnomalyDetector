//
// Created by Asaf on 08/01/2021.
//

#include "CommandDetectAnomalies.h"

string CommandDetectAnomalies::getDescription(){
    return this->description;
}

void CommandDetectAnomalies::execute() {
    HybridAnomalyDetector ad(this->threshold);
    ad.learnNormal(*this->shareKnowledge->tsTrain);
    this->shareKnowledge->anomalyReport = ad.detect(*this->shareKnowledge->tsTest);
    cout << "anomaly detection complete";
}