#pragma once

#ifndef _SIMPLE_MODULE_H_
#define	_SIMPLE_MODULE_H_

#include "Module_defines.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace Simple {

	class Module_Base {
	public:
		virtual void Init() = 0;
		virtual ~Module_Base() = default;
	};

    class GetModuleByName {
    public:
        using CreateFunc = std::unique_ptr<Module_Base>(*)();

        static GetModuleByName& getInstance();

        void registerClass(const std::string& className, CreateFunc createFunc);

        std::unique_ptr<Module_Base> createInstance(const std::string& className);

    private:
        GetModuleByName() = default;
        std::unordered_map<std::string, CreateFunc> registry;
    };

    template<class _ModuleTy>
    void RegisterModule(const std::string& designator) {
        GetModuleByName::getInstance().registerClass(designator, []() -> std::unique_ptr<Module_Base> {
            return std::make_unique<_ModuleTy>();
            });
    }
}
#endif // _SIMPLE_MODULE_H_