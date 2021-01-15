//
// Created by Asaf on 09/01/2021.
//

#include <iterator>
#include "CommandAnalyzeResults.h"
#include <iomanip>
static int N;

string CommandAnalyzeResults::getDescription(){
    return this->description;
}

void CommandAnalyzeResults::execute() {
    string line;
    vector<string> linesAnomalies;
    int P; // positive
    int timeSteps = this->shareKnowledge->tsTrain->table.begin()->second.size();
    N = timeSteps; // for now.
    this->dio->write("Please upload your local anomalies file.\n");
    line = this->dio->read();
    while (line != "done") {
        linesAnomalies.push_back(line);
        line = this->dio->read();
    }
    vector<string> continuousAR = collectAnomalies(linesAnomalies);
    P = continuousAR.size();
    measureAlgo(continuousAR, P, N, linesAnomalies);
}

void CommandAnalyzeResults::measureAlgo(vector<string> got, int P, int N, std::vector<string> expected) {
    int TP = 0; // true positive
    int FP = 0; // false positive

    for (int i = 0; i < got.size(); i++) {
        bool match = false;
        int pos = got[i].find(",");
        string from = got[i].substr(0, pos);
        string to = got[i].substr(pos + 1);
        int intFrom = std::stoi(from);
        int intTo = std::stoi(to);
        for (int j = 0; j < expected.size(); j++) {
            pos = got[i].find(",");
            string Exfrom = got[i].substr(0, pos);
            string Exto = got[i].substr(pos + 1);
            int intExFrom = std::stoi(Exfrom);
            int intExTo = std::stoi(Exto);

            if ((intFrom > intExTo && intTo > intExTo) && (intExFrom > intTo && intExTo > intTo))
                FP++;
            else
                match = true;
        }
        if (match)
            TP++;
    }
    float tpRate = TP / P;
    float fpRate = FP / N;
    this->dio->write("True Positive Rate: ");
    float rounded_down = floorf(tpRate * 1000) / 1000;
    this->dio->write(rounded_down);
    this->dio->write("\n");
    rounded_down = floorf(fpRate * 1000) / 1000;
    this->dio->write("False Positive Rate: ");
    this->dio->write(rounded_down);
    this->dio->write("\n");

}


vector<string> CommandAnalyzeResults::collectAnomalies(vector<string> expectedAnomalies) {
    vector<AnomalyReport> ar = this->shareKnowledge->anomalyReport;
    vector<string> continuousAR;
    int anomalyNum; // positive
    int i;
    for (int i = 0; i < ar.size() - 1; i++) {
        printf ("ar:::: %d\n", ar.size());
        string line = std::to_string(ar[i].timeStep) + ",";
        while (ar[i].timeStep + 1 == ar[i + 1].timeStep) {
            i++;
            anomalyNum++;
        }
        line = line + std::to_string(ar[i].timeStep);
        continuousAR.push_back(line);
    }
    N = ar.size() - anomalyNum;
    return continuousAR;

}

FILE CommandAnalyzeResults::createFile(vector<string> lines, string fileName) {
    ofstream file(fileName);

    std::ofstream output_file(fileName);
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(lines.begin(), lines.end(), output_iterator);

}


