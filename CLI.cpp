#include <iostream>
#include <stdlib.h>
#include "CLI.h"

using namespace std;


CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
}

void CLI::start() {

    ShareKnowledge shareKnowledge;
    bool exit = false;
    float choice;
    vector<Command*> commands;
    CommandUpload commandUpload(this->dio, &shareKnowledge);
    CommandAlgoSettings commandAlgoSettings(this->dio, &shareKnowledge);
    CommandDetectAnomalies commandDetectAnomalies(this->dio, &shareKnowledge);
    CommandDisplayResults commandDisplayResults(this->dio, &shareKnowledge);
    CommandAnalyzeResults commandAnalyzeResults(this->dio, &shareKnowledge);

    commands.push_back(&commandUpload);
    commands.push_back(&commandAlgoSettings);
    commands.push_back(&commandDetectAnomalies);
    commands.push_back(&commandDisplayResults);
    commands.push_back(&commandAnalyzeResults);

    this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
    for (int i = 0; i < commands.size(); ++i) {
        this->dio->write(commands.at(i)->getDescription());
    }
    this->dio->write("6.exit\n");
//    this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
//    this->dio->write("1.upload a time series csv file\n2.algorithm settings\n3.detect anomalies\n");
//    this->dio->write("4.display results\n5.upload anomalies and analyze results\n6.exit\n");
    this->dio->read(&choice);
    int intChoice = choice;
    while (choice != 6) {
        switch (intChoice) {
            case 1:
                commandUpload.execute();
                break;
            case 2:
                commandAlgoSettings.execute();
                break;
            case 3:
                commandDetectAnomalies.execute();
                break;
            case 4:
                commandDisplayResults.execute();
                break;
            case 5:
                commandAnalyzeResults.execute();
                break;
            case 6:
                exit = true;
                break;
            default:
                exit = true;
                break;
        }
        if (exit)
            break;
        this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        for (int i = 0; i < commands.size(); ++i) {
            this->dio->write(commands.at(i)->getDescription());
        }
        this->dio->write("6.exit\n");
        this->dio->read(&choice);
        intChoice = choice;
    }
}


CLI::~CLI() {
}

