//
// Created by Asaf on 09/01/2021.
//

#ifndef MITEX4_COMMANDDISPLAYRESULTS_H
#define MITEX4_COMMANDDISPLAYRESULTS_H
#include "CommandDisplayResults.h"
#include "commands.h"

class CommandDisplayResults:public Command {
protected:

public:


    CommandDisplayResults(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
            this->shareKnowledge = sKnow;
    }
    void execute();

    string getDescription();

    virtual ~CommandDisplayResults(){};


};


#endif //MITEX4_COMMANDDISPLAYRESULTS_H
