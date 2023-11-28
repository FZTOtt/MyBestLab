#ifndef VISUALISATOR_PLUGIN_H
#define VISUALISATOR_PLUGIN_H

#include "BasePlugin.h"
#include <vector>

class VisualisatorPlugin : public BasePlugin {
public:
    VisualisatorPlugin();

    // Переопределение метода получения типа плагина
    virtual std::string getPluginType() override{
        return "Visualisator";
    };

    // Переопределение метода получения имени плагина
    //virtual std::string getPluginName() override;

    virtual void GetData() = 0;

    // Метод для записи данных в массив
    void SetData(const std::vector<std::vector<double>>& newData){
        data = newData;
    };

    void SetTime(double _startTime, double _endTime, double _stepSize, double _numArguments){
        startTime = _startTime;
        endTime = _endTime;
        stepSize = _stepSize;
        numArguments = _numArguments;
    }

protected:
    // Массив данных
    std::vector<std::vector<double>> data;
    double startTime;
    double endTime;
    double stepSize;
    double numArguments;
};

#endif // VISUALISATOR_PLUGIN_H
