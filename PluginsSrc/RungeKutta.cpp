#include "SolvePlugin.h"
#include <vector>
#include <functional>

class RungeKutta : public PluginSolver {

public:

    virtual std::string getPluginName() override {
        return "RungeKutta";
    }

    void Solve() override {
        std::vector<double> k1, k2, k3, k4;
        double t = startTime;
        while(t < endTime ){

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
            t += stepSize;
            k1.clear();
            k2.clear();
            k3.clear();
            k4.clear();

        }
    }

};

extern "C" PluginSolver* registerPlugin() {
    return new RungeKutta();
}