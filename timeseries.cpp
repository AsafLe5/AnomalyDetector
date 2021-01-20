#include <fstream>
#include <iosfwd>
#include <string>
#include "timeseries.h"

TimeSeries::TimeSeries(const char *CSVfileName) {
    std::string line, val;
    this->csv.open(CSVfileName); // Open the given CSV file.
    int i = 0;
    vector<vector<string>> csvTwoD; // Two dimensional vector of string, represent the whole CSV file.
    while (std::getline(this->csv, line)) {
        vector<float> vals;
        std::stringstream str(line);
        vector<string> row;
        while (getline(str, val, ',')) // Separates each square of the CSV file for csvTwoD.
            row.push_back(val);
        csvTwoD.push_back(row);
        i++;
    }
    // Transpose the csvTwoD to get the correct order of lines as in the CVS file.
    vector<vector<string>> transVec(csvTwoD[0].size(), vector<string>());
    for (int i = 0; i < csvTwoD.size(); i++) {
        for (int j = 0; j < csvTwoD[i].size(); j++)
            transVec[j].push_back(csvTwoD[i][j]);
    }
    map<std::string, vector<float>>::iterator itMap;
    for (int i = 0; i < transVec.size(); i++) { // Loop through the map.
        vector<float> col;
        for (int j = 0; j < transVec[i].size(); ++j) { // checks whether we are in the first line.
            if (j == 0) // Case line is 0 then it means its the title of the column.
                continue;
            col.push_back(std::stof(transVec[i][j]));
        }
        this->table.insert({transVec[i][0], col}); // Adding the titles and column to the map.
    }
}


