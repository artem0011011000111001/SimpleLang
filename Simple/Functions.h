#pragma once

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Simple_typedefs.h"
#include "Variable.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

namespace Simple {

	struct Functions {
	private:
		static Funcs_t functions;

	public:

		static bool IsExist(const String& key);

		static FunctionPtr Get(const String& key);

		static void Set(const String& key, FunctionPtr value);

		static void RegisterDynamicFunction(const String& name, std::function<VALUE(Args_t)> funcbody, const size_t argscount);

		static void CreateStandartFunctions();
	};
}

#endif // _FUNCTIONS_H_