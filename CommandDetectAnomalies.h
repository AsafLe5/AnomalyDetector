//
// Created by Asaf on 08/01/2021.
//

#ifndef MITEX4_COMMANDDETECTANOMALIES_H
#define MITEX4_COMMANDDETECTANOMALIES_H
#include "commands.h"

class CommandDetectAnomalies:public Command {

public:
    virtual void execute();

    CommandDetectAnomalies(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
            this->shareKnowledge = sKnow;
    }

    FILE createFile(vector<string> lines, string fileName);
    string getDescription();

};


#endif //MITEX4_COMMANDDETECTANOMALIES_H
