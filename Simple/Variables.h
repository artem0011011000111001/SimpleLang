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
		static Vars_t variables;

		static std::stack<Vars_t> variablesState;

	public:

		static bool IsExist(const WString& key);

		static bool IsConstant(const WString& key);

		static ValuePtr Get(const WString& key);

		static Value& GetRef(const WString& key);

		static void SetAllVariables(Vars_t&& variables);

		static const std::unordered_map<WString, Variable>& GetAllVariables();

		static void Set(const WString& key, Variable value);

		static void SetNew(const WString& key, Variable value);

		static std::unordered_map<WString, Variable> CreateStandartVariables();

		static void PushState();

		static void PopState();

		static bool StateEmpty();
	};
}

#endif // !_VARIABLES_H_