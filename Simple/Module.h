#pragma once

#ifndef _SIMPLE_MODULE_H_
#define	_SIMPLE_MODULE_H_

#include "Module_defines.h"
#include "Variable.h"
#include "Variables.h"
#include "Function.h"
#include "Functions.h"
#include "Structs.h"
#include "Field_info.h"

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
        using CreateFunc = Ptr<Module_Base>(*)();

        static CreateModuleByName& getInstance();

        void registerClass(const WString& className, CreateFunc createFunc);

        Ptr<Module_Base> createInstance(const WString& className);

    private:
        CreateModuleByName() = default;
        WStr_map<CreateFunc> registry;
    };

    template<class _ModuleTy>
    void RegisterModule(const WString& designator) {
        CreateModuleByName::getInstance().registerClass(designator, []() -> std::unique_ptr<Module_Base> {
            return CREATE_PTR<_ModuleTy>();
            });
    }
}
#endif // _SIMPLE_MODULE_H_