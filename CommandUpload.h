//
// Created by Asaf on 08/01/2021.
//

#ifndef MITEX4_COMMANDUPLOAD_H
#define MITEX4_COMMANDUPLOAD_H

#include "commands.h"

class CommandUpload:public Command {
protected:
    string headLine;

public:

    CommandUpload(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
        this->shareKnowledge = sKnow;
        this->description = "1. upload a time series csv file";
    }


    void execute();
     string getDescription();

    //virtual bool isAnomal(correlatedFeatures cf, Point *point);
    FILE createFile(vector<string> vector, string fileName);
};


#endif //MITEX4_COMMANDUPLOAD_H
