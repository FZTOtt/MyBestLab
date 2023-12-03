#ifndef PLUGIN_SOLVER_H
#define PLUGIN_SOLVER_H

#include "BasePlugin.h"
#include <functional>
#include <vector>

class PluginSolver : public BasePlugin {

protected:
    // Массив лямбда-функций для уравнений
    std::vector<std::function<double(double, const std::vector<double>&)>> equations;
    std::vector<double> init;
    double startTime;
    double endTime;
    double stepSize;

public:
    std::vector<std::vector<double>> solution;
    
    PluginSolver() {};

    // Переопределение метода получения типа плагина
    virtual std::string getPluginType() override{
        return "solver";
    };

    // Переопределение метода получения имени плагина
    //virtual std::string getPluginName() const override;

    // Метод для установки уравнения с использованием лямбда-функций
    void SetEquation(const std::vector<std::function<double(double, const std::vector<double>&)>>& _equations){
        equations = _equations;
    };

    void SetInit(const std::vector<double>& initial){
        init = initial;
        solution.push_back(init);
    }
    
    void SetTime(double _startTime, double _endTime, double _stepSize){
        startTime = _startTime;
        endTime = _endTime;
        stepSize = _stepSize;
    }

    virtual void Solve() = 0;

};

#endif // PLUGIN_SOLVER_H
