//
// Created by Asaf on 08/01/2021.
//

#include "CommandAlgoSettings.h"

string CommandAlgoSettings::getDescription(){
    return this->description;
}

void CommandAlgoSettings::execute() {
    float newThreshold;
    cout << "The current correlation threshold is " << this->threshold;
    cout << "\nType a new threshold\n";
    cin >> newThreshold;
    while (newThreshold > 1 || newThreshold < 0) {
        std::cout << "please choose a value between 0 and 1";
        cin >> newThreshold;
    }
    this->shareKnowledge->threshold = newThreshold;

}