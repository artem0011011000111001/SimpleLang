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
		static std::unordered_map<String, Variable> variables;

		static std::stack<std::unordered_map<String, Variable>> variablesState;

	public:

		static bool IsExist(const String& key);

		static bool IsConstant(const String& key);

		static ValuePtr Get(const String& key);

		static Value& GetRef(const String& key);

		static void SetAllVariables(std::unordered_map<String, Variable>&& variables);

		static const std::unordered_map<String, Variable>& GetAllVariables();

		static void Set(const String& key, Variable value);

		static void SetNew(const String& key, Variable value);

		static std::unordered_map<String, Variable> CreateStandartVariables();

		static void PushState();

		static void PopState();
	};
}

#endif // !_VARIABLES_H_