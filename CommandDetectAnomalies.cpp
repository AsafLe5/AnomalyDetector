//
// Created by Asaf on 08/01/2021.
//
#include <iterator>
#include "CommandDetectAnomalies.h"

string CommandDetectAnomalies::getDescription(){
    return this->description;
}

void CommandDetectAnomalies::execute() {
    string line;
    vector<string> linesAnomalyReport;
    TimeSeries tsTrain("flightTrain.csv");
    TimeSeries tsTest("flightTest.csv");

    HybridAnomalyDetector ad(this->threshold);
    ad.learnNormal(tsTrain);
    vector<AnomalyReport> anomalyReport =  ad.detect(tsTest);

    auto it = anomalyReport.begin();
    line = it->description +","+ std::to_string(it->timeStep);

    while (line != "done") {
        linesAnomalyReport.push_back(line);
        it++;
        if (it == anomalyReport.end())
            break;
        line = it->description +","+ std::to_string(it->timeStep);
    }
    createFile(linesAnomalyReport,"anomalyReport.csv");

    ad.learnNormal(*this->shareKnowledge->tsTrain);
    this->shareKnowledge->anomalyReport = ad.detect(*this->shareKnowledge->tsTest);
    this->dio->write("anomaly detection complete\n");
}

FILE CommandDetectAnomalies::createFile(vector<string> lines, string fileName) {

    ofstream file(fileName);

    std::ofstream output_file(fileName);
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(lines.begin(), lines.end(), output_iterator);
}