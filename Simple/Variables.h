#pragma once

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "Simple_typedefs.h"
#include "AST.h"
#include "Parser.h"
#include "Variable.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <stack>

namespace Simple {

	struct Variables {
	private:
		static std::unordered_map<std::string, Variable> variables;

		static std::stack<std::unordered_map<std::string, Variable>> variablesState;

	public:

		static bool IsExist(const std::string& key);

		static bool IsConstant(const std::string& key);

		static ValuePtr Get(const std::string& key);

		static Value& GetRef(const std::string& key);

		static void SetAllVariables(std::unordered_map<std::string, Variable>&& variables);

		static const std::unordered_map<std::string, Variable>& GetAllVariables();

		static void Set(const std::string& key, Variable value);

		static void SetNew(const std::string& key, Variable value);

		static std::unordered_map<std::string, Variable> CreateStandartVariables();

		static void PushState();

		static void PopState();
	};
}

#endif // !_VARIABLES_H_