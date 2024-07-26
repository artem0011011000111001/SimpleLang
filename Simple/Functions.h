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
		static std::unordered_map<std::string, FunctionPtr> functions;

	public:

		static bool IsExist(const std::string& key);

		static FunctionPtr Get(const std::string& key);

		static Function& GetRef(const std::string& key);

		static void Set(const std::string& key, FunctionPtr value);

		static void RegisterDynamicFunction(const std::string& name, std::function<VALUE(Args_t)> funcbody, const size_t argscount);

		static void CreateStandartFunctions();
	};
}

#endif // _FUNCTIONS_H_