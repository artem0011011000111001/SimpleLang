#pragma once

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "Simple_typedefs.h"
#include "AST.h"
#include "Parser.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <stack>

namespace Simple {

	struct Variables {
	private:
		static std::unordered_map<std::string, ValuePtr> variables;

		static std::vector<std::string> constants;

		static std::stack<std::unordered_map<std::string, ValuePtr>> variablesState;
		static std::stack<std::vector<std::string>> constantsState;

	public:

		static bool IsExist(const std::string& key);

		static bool IsConstant(const std::string& key);

		static ValuePtr Get(const std::string& key);

		static void SetAllVariables(std::unordered_map<std::string, ValuePtr>&& variables);

		static void SetAllConstants(const std::vector<std::string>& constants);

		static const std::unordered_map<std::string, ValuePtr>& GetAllVariables();

		static const std::vector<std::string>& GetAllConstants();

		static void Set(const std::string& key, ValuePtr value);

		static void AddConstant(const std::string& key);

		static void RemoveConstant(const std::string& key);

		static std::unordered_map<std::string, ValuePtr> CreateStandartVariables();

		static void PushState();

		static void PopState();
	};
}

#endif // !_VARIABLES_H_