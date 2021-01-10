

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

//#include "CommandAlgoSettings.h"
//#include "CommandDetectAnomalies.h"
//#include "CommandDisplayResults.h"
//#include "CommandUpload.h"
//#include "CommandAnalyzeResults.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    vector<Command> commands;
    // you can add data members
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
};

#endif /* CLI_H_ */
