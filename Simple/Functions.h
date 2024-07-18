#pragma once

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Simple_typedefs.h"

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

		static void Set(const std::string& key, FunctionPtr value);

		static void RegisterDynamicFunction(const std::string& name, std::function<ValuePtr(std::vector<ValuePtr>)> funcbody, const std::vector<size_t>& argscount);

		static std::unordered_map<std::string, FunctionPtr> CreateStandartFunctions();
	};
}

#endif // !_FUNCTIONS_H_