//
// Created by Asaf on 08/01/2021.
//

#include "CommandAlgoSettings.h"

string CommandAlgoSettings::getDescription(){
    return "algorithm settings";
}

void CommandAlgoSettings::execute() {
    float newThreshold;
    this->dio->write("The current correlation threshold is ");
    this->dio->write(this->threshold);
    this->dio->write("\nType a new threshold\n");
    this->dio->read(&newThreshold);
    while (newThreshold > 1 || newThreshold < 0) {
        this->dio->write("please choose a value between 0 and 1");

    }
    this->shareKnowledge->threshold = newThreshold;

}