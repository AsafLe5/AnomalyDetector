

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <string.h>
#include <iterator>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include "timeseries.h"
#include <unistd.h>
#include <fstream>

class ShareKnowledge {
protected:

public:
    ShareKnowledge() {

    }

    TimeSeries *tsTrain;
    TimeSeries *tsTest;

    int timeStepsSize;

    HybridAnomalyDetector *hybridAnomalyDetector;
    vector<AnomalyReport> anomalyReport;
    float threshold;

    //ShareKnowledge() { }
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
class SocketIO : public DefaultIO{
    int socket;
public:
    SocketIO(int socket) : socket(socket) {}
    virtual string read(){
        string clientInput="";
        char c=0;
        ::read(socket,&c,sizeof(char));
        while(c!='\n'){
            clientInput+=c;
            ::read(socket,&c,sizeof(char));
        }
        return clientInput;
    }
    virtual void write(string text){
        ::write(socket,text.c_str(),text.length());
    }
    virtual void write(float f){
        std::ostringstream s;
        s << f;
        ::write(socket, s.str().c_str(), s.str().length());
    }
    virtual void read(float* f){
        string serverInput="";
        char c=0;
        ::read(socket,&c,sizeof(char));
        while(c!='\n'){
            serverInput+=c;
            ::read(socket,&c,sizeof(char));
        }
        *f = stof(serverInput);
    }
    virtual ~SocketIO(){}
};
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


class CommandUpload:public Command {
protected:

public:

    CommandUpload(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
        this->shareKnowledge = sKnow;
    }
    //1.upload a time series csv file\n2.algorithm settings\n3.detect anomalies\n");
//    this->dio->write("4.display results\n5.upload anomalies and analyze results\n6.exit\n");

    string getDescription(){
        return "1.upload a time series csv file\n";
    }

    void execute() {
        string line;
        vector<string> linesTrain;
        vector<string> linesTest;

        this->dio->write("Please upload your local train CSV file.\n");
        line = this->dio->read();
        while (line != "done") {
            linesTrain.push_back(line);
            line = this->dio->read();
        }
        createFile(linesTrain,"anomalyTrain.csv");

        this->dio->write("Upload complete.\n");

        this->dio->write("Please upload your local test CSV file.\n");
        line = this->dio->read();
        while (line != "done") {
            linesTest.push_back(line);
            line = this->dio->read();
        }
        createFile(linesTest, "anomalyTest.csv");
        this->dio->write("Upload complete.\n");

    }

    FILE createFile(vector<string> lines, string fileName) {

        ofstream file(fileName);

        std::ofstream output_file(fileName);
        std::ostream_iterator<std::string> output_iterator(output_file, "\n");
        std::copy(lines.begin(), lines.end(), output_iterator);
    }
};



class CommandAlgoSettings:public Command {
protected:

public:

    CommandAlgoSettings(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
        this->shareKnowledge = sKnow;
    }

    string getDescription(){
        return "2.algorithm settings\n";
    }

    void execute() {
        float newThreshold;
        this->dio->write("The current correlation threshold is ");
        this->dio->write(this->threshold);
        this->dio->write("\nType a new threshold\n");
        this->dio->read(&newThreshold);
        while (newThreshold > 1 || newThreshold < 0) {
            this->dio->write("please choose a value between 0 and 1\n");

        }
        this->shareKnowledge->threshold = newThreshold;
    }

};


class CommandDetectAnomalies:public Command {

public:


    CommandDetectAnomalies(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
        this->shareKnowledge = sKnow;
    }

    string getDescription(){
        return "3.detect anomalies\n";
    }

    void execute() {
        string line;
        vector<string> linesAnomalyReport;
        TimeSeries tsTrain("anomalyTrain.csv");
        TimeSeries tsTest("anomalyTest.csv");
        this->shareKnowledge->timeStepsSize = tsTrain.table.begin()->second.size();
        HybridAnomalyDetector ad(this->threshold);

        ad.learnNormal(tsTrain);
        this->shareKnowledge->anomalyReport = ad.detect(tsTest);
        this->dio->write("anomaly detection complete.\n");
    }

};


class CommandDisplayResults:public Command {
protected:

public:


    CommandDisplayResults(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
        this->shareKnowledge = sKnow;
    }

    string getDescription(){
        return "4.display results\n";
    }

    void execute() {
        for (int i = 0; i < this->shareKnowledge->anomalyReport.size(); i++) {
            this->dio->write(this->shareKnowledge->anomalyReport.at(i).timeStep);
            this->dio->write("\t ");
            this->dio->write(this->shareKnowledge->anomalyReport.at(i).description);
            this->dio->write("\n");
        }
        this->dio->write("Done.\n");
    }

};
static float N;

class CommandAnalyzeResults:public Command {

public:


    CommandAnalyzeResults(DefaultIO* dio, ShareKnowledge *sKnow):Command(dio){
        this->shareKnowledge = sKnow;
    }

    string getDescription(){
        return "5.upload anomalies and analyze results\n";
    }

    void execute() {
        N=0;
        string line;
        vector<string> linesAnomalies;
        float P; // positive
        int timeSteps = this->shareKnowledge->timeStepsSize;
        N = timeSteps; // for now.
        this->dio->write("Please upload your local anomalies file.\n");
        line = this->dio->read();
        while (line != "done") {
            linesAnomalies.push_back(line);
            line = this->dio->read();
        }
        this->dio->write("Upload complete.\n");
        vector<string> continuousAR = collectAnomalies(linesAnomalies);
        P = linesAnomalies.size();
        measureAlgo(continuousAR, P, linesAnomalies);
    }

    void measureAlgo(vector<string> got, float P, std::vector<string> expected) {
        float TP = 0; // true positive
        float FP = 0; // false positive

        for (int i = 0; i < got.size(); i++) {
            bool match = false;
            int pos = got[i].find(",");
            string from = got[i].substr(0, pos);
            string to = got[i].substr(pos + 1);
            int intFrom = std::stoi(from);
            int intTo = std::stoi(to);
            for (int j = 0; j < expected.size(); j++) {
                pos = expected[j].find(",");
                string Exfrom = expected[j].substr(0, pos);
                string Exto = expected[j].substr(pos + 1);
                int intExFrom = std::stoi(Exfrom);
                int intExTo = std::stoi(Exto);

                if ((intFrom > intExTo && intTo > intExTo) || (intExFrom > intTo && intExTo > intTo))
                    continue;
                else
                    match = true;
            }
            if (match)
                TP++;
            else
                FP++;
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


    vector<string> collectAnomalies(vector<string> expectedAnomalies) {
        vector<AnomalyReport> ar = this->shareKnowledge->anomalyReport;
        vector<string> continuousAR;
        int anomalyNum=0; // positive
        int i;
        for (int i = 0; i < ar.size() - 1; i++) {
            string line = std::to_string(ar[i].timeStep) + ",";
            while (ar[i].timeStep + 1 == ar[i + 1].timeStep) {
                i++;
                anomalyNum++;
            }
            line = line + std::to_string(ar[i].timeStep);
            continuousAR.push_back(line);
        }
        N = this->shareKnowledge->timeStepsSize - anomalyNum;
        return continuousAR;

    }
};






// implement here your command classes



#endif /* COMMANDS_H_ */
