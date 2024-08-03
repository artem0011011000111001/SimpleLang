#pragma once

#ifndef _SIMPLE_MODULE_H_
#define	_SIMPLE_MODULE_H_

#include "Module_defines.h"
#include "Variable.h"
#include "Variables.h"
#include "Function.h"
#include "Functions.h"
#include "Structs.h"

#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <iterator>

namespace Simple {

	class Module_Base {
	public:
		virtual void Init() = 0;
		virtual ~Module_Base() = default;
	};

    class CreateModuleByName {
    public:
        using CreateFunc = std::unique_ptr<Module_Base>(*)();

        static CreateModuleByName& getInstance();

        void registerClass(const String& className, CreateFunc createFunc);

        std::unique_ptr<Module_Base> createInstance(const String& className);

    private:
        CreateModuleByName() = default;
        std::unordered_map<String, CreateFunc> registry;
    };

    template<class _ModuleTy>
    void RegisterModule(const String& designator) {
        CreateModuleByName::getInstance().registerClass(designator, []() -> std::unique_ptr<Module_Base> {
            return std::make_unique<_ModuleTy>();
            });
    }
}
#endif // _SIMPLE_MODULE_H_