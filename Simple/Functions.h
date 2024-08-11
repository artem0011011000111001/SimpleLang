#pragma once

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Simple_typedefs.h"
#include "Variable.h"
#include "FuncParams.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

namespace Simple {

	struct Functions {
	private:
		static Funcs_t functions;

	public:

		static bool IsExist(const WString& key, int argsCount = not_specified_args);

		static FunctionPtr Get(const WString& key, int argsCount);

		static FuncParams Get(const WString& key);

		static void Set(const WString& key, FunctionPtr func, int argsCount);

		static void RegisterDynamicFunction(const WString& name, std::function<VALUE(Args_t)> funcbody, const int argscount);

		static void CreateStandartFunctions();
	};
}

#endif // _FUNCTIONS_H_