//
// Created by Asaf on 08/01/2021.
//

#ifndef MITEX4_COMMANDALGOSETTNINGS_H
#define MITEX4_COMMANDALGOSETTNINGS_H

#include "commands.h"


class CommandAlgoSettings:public Command {
protected:
    string headLine;
public:



    CommandAlgoSettings(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
            this->shareKnowledge = sKnow;
    }

    string getDescription();

    void execute();

};


#endif //MITEX4_COMMANDALGOSETTNINGS_H
