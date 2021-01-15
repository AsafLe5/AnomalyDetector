//
// Created by Asaf on 08/01/2021.
//

#include <iterator>
#include "CommandUpload.h"

string CommandUpload::getDescription(){
    return this->description;
}

void CommandUpload::execute() {
    string line;
    vector<string> linesTrain;
    vector<string> linesTest;

    this->dio->write("Please upload your local train CSV file.\n");
    line = this->dio->read();
    while (line != "done") {
        linesTrain.push_back(line);
        line = this->dio->read();
    }
    createFile(linesTrain,"flightTrain.csv");
    TimeSeries tsTrain("flightTrain.csv");

    this->dio->write("Please upload your local test CSV file.\n");
    line = this->dio->read();
    while (line != "done") {
        linesTest.push_back(line);
        line = this->dio->read();
    }
    createFile(linesTest, "flightTest.csv");
    TimeSeries tsTest("flightTest.csv");


    this->shareKnowledge->tsTrain = &tsTrain;
    this->shareKnowledge->tsTest = &tsTest;

}

FILE CommandUpload::createFile(vector<string> lines, string fileName) {

    ofstream file(fileName);

    std::ofstream output_file(fileName);
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(lines.begin(), lines.end(), output_iterator);
}
