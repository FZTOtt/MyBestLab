#include "SolvePlugin.h"
#include <vector>
#include <functional>

class AdamsBashfortMoulton : public PluginSolver {

public:

    virtual std::string getPluginName() override {
        return "AdamsBashfortMoulton";
    }

    void Solve() override {
        std::vector<double> predicted(equations.size());
        double t = startTime;
        for (int i = 0; i < 2; i++){
            RungeKuttaStep(t, stepSize);
            solution.push_back(init);
            t += stepSize;
        }
        while (t <= endTime) {
                for (int i = 0; i < equations.size(); i++){
                    predicted[i] = solution[-1][i] + (stepSize / 24) * 
                        (55 * equations[i](t, solution[-1]) 
                            - 59 * equations[i](t, solution[-2]) 
                                + 37 * equations[i](t, solution[-3]) 
                                    - 9 * equations[i](t, solution[-4]));

                }
                
                solution.push_back(predicted);

                for (int i = 0; i < equations.size(); i++){
                    predicted[i] = solution[-1][i] + (stepSize / 24) * 
                        (9 * equations[i](t, solution[-1]) 
                            + 19 * equations[i](t, solution[-2]) 
                                - 5 * equations[i](t, solution[-3]) 
                                    + 1 * equations[i](t, solution[-4]));
                }    
                solution[-1] = predicted;
                t += stepSize;
            }
    }

private:
    void RungeKuttaStep(double t, double stepSize) {

        std::vector<double> k1, k2, k3, k4;

        for (int i = 0; i < equations.size(); i++){
            k1.push_back(equations[i](t, init));
        }

        for (int i = 0; i < equations.size(); i++){
            std::vector<double> args;
            for (int i = 0; i < equations.size(); i++){
                args.push_back(init[i] + k1[i] * stepSize / 2);
            }
            k2.push_back(equations[i](t + stepSize / 2, init));
        }
        
        for (int i = 0; i < equations.size(); i++){
            std::vector<double> args;
            for (int i = 0; i < equations.size(); i++){
                args.push_back(init[i] + k2[i] * stepSize / 2);
            }
            k3.push_back(equations[i](t + stepSize / 2, init));
        }

        for (int i = 0; i < equations.size(); i++){
            std::vector<double> args;
            for (int i = 0; i < equations.size(); i++){
                args.push_back(init[i] + k3[i] * stepSize);
            }
            k4.push_back(equations[i](t + stepSize, init));
        }

        for (int i = 0; i < equations.size(); i++){
            init[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6 * stepSize;
        }
    }
};
// Функция регистрации плагина в системе
extern "C" PluginSolver* registerPlugin() {
    return new AdamsBashfortMoulton();
}
