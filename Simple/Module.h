#pragma once

#ifndef _SIMPLE_MODULE_H_
#define	_SIMPLE_MODULE_H_

#include "Module_defines.h"
#include "Variable.h"
#include "Variables.h"
#include "Function.h"
#include "Functions.h"

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

        void registerClass(const std::string& className, CreateFunc createFunc);

        std::unique_ptr<Module_Base> createInstance(const std::string& className);

    private:
        CreateModuleByName() = default;
        std::unordered_map<std::string, CreateFunc> registry;
    };

    template<class _ModuleTy>
    void RegisterModule(const std::string& designator) {
        CreateModuleByName::getInstance().registerClass(designator, []() -> std::unique_ptr<Module_Base> {
            return std::make_unique<_ModuleTy>();
            });
    }
}
#endif // _SIMPLE_MODULE_H_