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
        solution.push_back(init);
    }

};

extern "C" PluginSolver* registerPlugin() {
    return new RungeKutta();
}