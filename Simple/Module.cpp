#include "Module.h"

using namespace Simple;

GetModuleByName& GetModuleByName::getInstance() {
    static GetModuleByName instance;
    return instance;
}

void GetModuleByName::registerClass(const std::string& className, CreateFunc createFunc) {
    registry[className] = createFunc;
}

std::unique_ptr<Module_Base> GetModuleByName::createInstance(const std::string& className) {
    auto it = registry.find(className);
    if (it != registry.end()) {
        return it->second();
    }
    return nullptr;
}
