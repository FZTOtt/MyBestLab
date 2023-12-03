#include "BasePlugin.h"
#include "SolvePlugin.h"
#include "VisualisatorPlugin.h"
#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <functional>
#include <dirent.h>
#include <fstream>


int main() {
    // Укажите путь к папке с библиотеками
    const char* pluginFolderPath = "./Plagins";


    std::ofstream file;
    file.open("Log.txt");


    // Открываем папку
    DIR* dir = opendir(pluginFolderPath);
    if (!dir) {
        std::cerr << "Failed to open the plugin folder." << std::endl;
        return 1;
    }

    void* pluginHandle;
    BasePlugin* plugin;
    PluginSolver* solverPlugin;
    VisualisatorPlugin* visualisatorPlugin;
    // Перебираем файлы в папке
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Это обычный файл
            // Формируем полный путь к файлу
            std::string filePath = std::string(pluginFolderPath) + "/" + entry->d_name;

            // Загружаем библиотеку
            pluginHandle = dlopen(filePath.c_str(), RTLD_LAZY);
            if (!pluginHandle) {
                std::cerr << "Failed to load the plugin: " << dlerror() << std::endl;
                continue;
            }

            // Получаем указатель на функцию registerPlugin
            using RegisterPluginFunc = BasePlugin* (*)();
            RegisterPluginFunc registerPlugin = reinterpret_cast<RegisterPluginFunc>(dlsym(pluginHandle, "registerPlugin"));
            if (!registerPlugin) {
                std::cerr << "Failed to get registerPlugin function: " << dlerror() << std::endl;
                dlclose(pluginHandle);
                continue;
            }

            // Создаем объект плагина
            plugin = registerPlugin();
            
            // Проверяем, является ли тип плагина "Solver"
            if (plugin->getPluginType() == "solver") {
                file << "Found " << plugin->getPluginName() << std::endl;
                solverPlugin = dynamic_cast<PluginSolver*>(plugin);
                std::cout << "Found a Solver plugin: " << entry->d_name << std::endl;
            }
            else if (plugin->getPluginType() == "Visualisator"){
                file << "Found " << plugin->getPluginName() << std::endl;
                visualisatorPlugin = dynamic_cast<VisualisatorPlugin*>(plugin);
                std::cout << "Found a Visualisator plugin: " << entry->d_name << std::endl;
            }

            // Освобождаем ресурсы
            
        }
    }

    std::vector<std::function<double(double, const std::vector<double>&)>> equations;
    auto x1 = [](double t, std::vector<double> x){
        return (double) -0.577*x[0];
    };
    auto x2 = [](double t, std::vector<double> x){
        return (double) 0.577*x[0] - 0.422*x[1];
    };
    auto x3 = [](double t, std::vector<double> x){
        return (double) 0.422*x[1];
    };
    equations.push_back(x1);
    equations.push_back(x2);
    equations.push_back(x3);
    std::cout<<equations.size();
    solverPlugin->SetEquation(equations);

    std::vector<double> init{1,0,0};

    solverPlugin->SetInit(init);
    solverPlugin->SetTime(0, 10, 0.1);

    file << "Use " << solverPlugin->getPluginName() << " as a solver" << std::endl;

    solverPlugin->Solve();

    std::vector<std::vector<double>> solution = solverPlugin->solution;

    visualisatorPlugin->SetData(solution);
    visualisatorPlugin->SetTime(0, 10, 0.1, 3);
    visualisatorPlugin->GetData();

    file << "Use " << visualisatorPlugin->getPluginName() << " as a visualisator" << std::endl;

    delete plugin;
    dlclose(pluginHandle);
    std::cout << "end";
    // Закрываем папку
    closedir(dir);

    return 0;
}
