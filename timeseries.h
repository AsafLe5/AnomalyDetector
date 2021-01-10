#include <fstream>
#include <iosfwd>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include "string"

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries {
private:
    std::ifstream csv;
public:
    map<std::string, vector<float>> table;
    explicit TimeSeries(const char *CSVfileName);
};
#endif /* TIMESERIES_H_ */
