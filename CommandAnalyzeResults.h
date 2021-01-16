//
// Created by Asaf on 09/01/2021.
//

#ifndef MITEX4_COMMANDANALYZERESULTS_H
#define MITEX4_COMMANDANALYZERESULTS_H
#include "CommandAnalyzeResults.h"
#include "commands.h"

class CommandAnalyzeResults:public Command {

public:
    virtual void execute();

    CommandAnalyzeResults(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
            this->shareKnowledge = sKnow;
    }

    FILE createFile(vector<string> vector, string fileName);

    vector<string> collectAnomalies(vector<string> expectedAnomalies);

    void measureAlgo(vector<string> vector, float p, std::vector<string> expected);

    string getDescription();
};


#endif //MITEX4_COMMANDANALYZERESULTS_H
