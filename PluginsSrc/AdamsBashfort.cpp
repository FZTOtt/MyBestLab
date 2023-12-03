#include "SolvePlugin.h"
#include <vector>
#include <functional>

class AdamsBashfort : public PluginSolver {

public:

    virtual std::string getPluginName() override {
        return "AdamsBashfort";
    }

    void Solve() override {
        std::vector<double> predicted(equations.size());
        double t = startTime;
        RungeKuttaStep(t, stepSize);
        t += stepSize;
            while (t <= endTime) {
                
                    for (int i = 0; i < equations.size(); i++){
                        predicted[i] = init[i] + (stepSize / 2) * 
                                (3 * equations[i](t, init) - equations[i](t - stepSize, solution[-1]));
                    }
                    solution.push_back(init);
                    init = predicted;
                    t += stepSize;
                    
            }
    }

private:
    void RungeKuttaStep(double t, double stepSize) {
        std::vector<double> k1, k2, k3, k4;
        for (int i = 0; i < equations.size(); i++){
            k1.push_back(equations[i](t, init));
        }

        std::vector<double> args1;
        for (int i = 0; i < equations.size(); i++){
            args1.push_back(init[i] + k1[i] * stepSize / 2);
        }

        for (int i = 0; i < equations.size(); i++){
            
            k2.push_back(equations[i](t + stepSize / 2, args1));
        }

        std::vector<double> args2;
        for (int i = 0; i < equations.size(); i++){
            args2.push_back(init[i] + k2[i] * stepSize / 2);
        }
        
        for (int i = 0; i < equations.size(); i++){
            
            k3.push_back(equations[i](t + stepSize / 2, args2));
        }

        std::vector<double> args3;
        for (int i = 0; i < equations.size(); i++){
            args3.push_back(init[i] + k3[i] * stepSize);
        }

        for (int i = 0; i < equations.size(); i++){
            
            k4.push_back(equations[i](t + stepSize, args3));
        }

        for (int i = 0; i < equations.size(); i++){
            init[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0 * stepSize;
        }
        solution.push_back(init);
    }
};
// Функция регистрации плагина в системе
extern "C" PluginSolver* registerPlugin() {
    return new AdamsBashfort();
}