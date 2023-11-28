#include "VisualisatorPlugin.h"
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>


class ToCSV : public VisualisatorPlugin {

public:

    virtual std::string getPluginName() override {
        return "ToCSV";
    }

    void GetData() override{

        std::ofstream file;
        file.open("ODESolve.csv");

        file << "t, ";
        for (int i = 1; i < numArguments; ++i){
            file << "x" << i << ", ";
        }
        file << "x" << numArguments << "\n";
        for (int i = 0; i < data.size(); ++i){
            std::cout << startTime << ", ";
            for (int j = 0; j < data[0].size() - 1; ++j){
                std::cout << data[i][j] << ", ";
            }
            std::cout << data[i][-1] << "\n";
            startTime+=stepSize;
        }
    }
};
extern "C" VisualisatorPlugin* registerPlugin() {
    return new ToCSV();
}
