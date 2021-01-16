#include <iostream>
#include <stdlib.h>
#include "CLI.h"
#include "commands.h"
#include "CommandUpload.h"
#include "CommandAlgoSettings.h"
#include "CommandDetectAnomalies.h"
#include "CommandDisplayResults.h"
#include "CommandAnalyzeResults.h"
//#include "ShareKnowledge.h"


using namespace std;


CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
}

void CLI::start() {

    ShareKnowledge shareKnowledge;
    bool exit = false;
    float choice;

    this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
    this->dio->write("1.upload a time series csv file\n2.algorithm settings\n3.detect anomalies\n");
    this->dio->write("4.display results\n5.upload anomalies and analyze results\n6.exit\n");
    this->dio->read(&choice);
    int intChoice = choice;
    while (choice != 6) {
        switch (intChoice) {
            case 1: {
                CommandUpload commandUpload(this->dio, &shareKnowledge);
                commandUpload.execute();
                break;
            }
            case 2: {
                CommandAlgoSettings commandAlgoSettings(this->dio, &shareKnowledge);
                commandAlgoSettings.execute();
                break;
            }
            case 3: {
                CommandDetectAnomalies commandDetectAnomalies(this->dio, &shareKnowledge);
                commandDetectAnomalies.execute();
                break;
            }
            case 4: {
                CommandDisplayResults commandDisplayResults(this->dio, &shareKnowledge);
                commandDisplayResults.execute();
                break;
            }
            case 5: {
                CommandAnalyzeResults commandAnalyzeResults(this->dio, &shareKnowledge);
                commandAnalyzeResults.execute();
                break;
            }
            case 6: {
                exit = true;
                break;
            }
            default:
                exit = true;
                break;
        }
        if (exit)
            break;
        this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        this->dio->write("1.upload a time series csv file\n2.algorithm settings\n3.detect anomalies\n");
        this->dio->write("4.display results\n5.upload anomalies and analyze results\n6.exit\n");
        this->dio->read(&choice);
        intChoice = choice;
    }
}


CLI::~CLI() {
}

