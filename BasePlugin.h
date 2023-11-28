#ifndef BASE_PLUGIN_H
#define BASE_PLUGIN_H

#include <string>

class BasePlugin {
public:
    virtual ~BasePlugin() {}

    // Метод для получения типа плагина
    virtual std::string getPluginType()  = 0;

    // Метод для получения имени плагина
    virtual std::string getPluginName()  = 0;
};

#endif // BASE_PLUGIN_H
