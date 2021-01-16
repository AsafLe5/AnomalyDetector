//
// Created by Asaf on 09/01/2021.
//

#include "CommandDisplayResults.h"

string CommandDisplayResults::getDescription(){
    return this->description;
}

void CommandDisplayResults::execute() {
    for (int i = 0; i < this->shareKnowledge->anomalyReport.size(); i++) {
        this->dio->write(this->shareKnowledge->anomalyReport.at(i).timeStep);
        this->dio->write("  ");
        this->dio->write(this->shareKnowledge->anomalyReport.at(i).description);
        this->dio->write("\n");

    }
    this->dio->write("Done.\n");
}