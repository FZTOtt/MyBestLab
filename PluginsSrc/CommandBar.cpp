#include "VisualisatorPlugin.h"
#include <vector>
#include <functional>
#include <iostream>


class CommandBar : public VisualisatorPlugin {

public:

    virtual std::string getPluginName() override {
        return "CommandBar";
    }

    void GetData() override{
        std::cout << "t, ";
        for (int i = 1; i < numArguments; ++i){
            std::cout << "x" << i << ", ";
        }
        std::cout << "x" << numArguments << std::endl;
        int count=0;
        for (int i = 0; i < data.size(); ++i){
            std::cout << startTime << ", ";
            for (int j = 0; j < data[0].size() - 1; ++j){
                std::cout << data[i][j] << ", ";
            }
            std::cout << data[i][-1] << std::endl;
            startTime+=stepSize;
        }
    }
    
};
extern "C" VisualisatorPlugin* registerPlugin() {
    return new CommandBar();
}
