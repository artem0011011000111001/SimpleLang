#include "Module.h"

using namespace Simple;

CreateModuleByName& CreateModuleByName::getInstance() {
    static CreateModuleByName instance;
    return instance;
}

void CreateModuleByName::registerClass(const WString& className, CreateFunc createFunc) {
    registry[className] = createFunc;
}

Ptr<Module_Base> CreateModuleByName::createInstance(const WString& className) {
    auto it = registry.find(className);
    if (it != registry.end()) {
        return it->second();
    }
    return nullptr;
}
