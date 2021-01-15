

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include "timeseries.h"
#include "ShareKnowledge.h"
//#include "CLI.h"
//#include "ShareKnowledge.h"



class ShareKnowledge {
protected:

public:
    TimeSeries *tsTrain;
    TimeSeries *tsTest;

    HybridAnomalyDetector *hybridAnomalyDetector;
    vector<AnomalyReport> anomalyReport;
    float threshold;

    ShareKnowledge() { }
};



using namespace std;

class DefaultIO{
protected:

public:

    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}
    // you may add additional methods here
};

// you may add here helper classes
//public ShareKnowledge

// you may edit this class
class Command{

protected:
    DefaultIO* dio;
    string description;
    FILE fileTrain;
    FILE fileTest;
    ShareKnowledge *shareKnowledge;

    float threshold=0.9; //להוסיף גם בשאר הקבצים, לשנות את define!!!!!!!!
public:

    Command(DefaultIO* dio):dio(dio){}

    Command() {}

    virtual void execute()=0;

    virtual string getDescription()=0;

    virtual ~Command(){}

};





// implement here your command classes



#endif /* COMMANDS_H_ */
