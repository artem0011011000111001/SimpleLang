#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "Simple_typedefs.h"
#include "Variable.h"

#include <string>
#include <unordered_map>

namespace Simple {

	struct Variable;

	enum class ValueType {
		NUMBER,
		STRING,
		STRUCT
	};

	enum class LogicOperators {
		EQUALS,
		NOT_EQUALS,

		LT,
		LTEQ,
		GT,
		GTEQ,

		AND,
		OR
	};

	enum class BinaryOperators {
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		POWER
	};

	double strict_stod(const std::string str);
	//ValueType IdentifyValueType(const ValuePtr& valuePtr);
	std::string to_string(LogicOperators op);
	std::string to_string(BinaryOperators op);
	void copy_variables(const std::unordered_map<std::string, Variable>& from, std::unordered_map<std::string, Variable>& whom);
}
#endif // _UTILS_H_