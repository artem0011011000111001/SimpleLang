#include "Module.h"

using namespace Simple;

CreateModuleByName& CreateModuleByName::getInstance() {
    static CreateModuleByName instance;
    return instance;
}

void CreateModuleByName::registerClass(const String& className, CreateFunc createFunc) {
    registry[className] = createFunc;
}

std::unique_ptr<Module_Base> CreateModuleByName::createInstance(const String& className) {
    auto it = registry.find(className);
    if (it != registry.end()) {
        return it->second();
    }
    return nullptr;
}
