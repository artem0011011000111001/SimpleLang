#pragma once

#ifndef _OTHER_H_
#define _OTHER_H_

#include "Simple_typedefs.h"

#include <string>
#include <unordered_map>

namespace Simple {

	enum class ValueType
	{
		NUMBER,
		STRING
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
	ValueType IdentifyValueType(const ValuePtr& valuePtr);
	std::string to_string(LogicOperators op);
	std::string to_string(BinaryOperators op);
	std::string to_string(ValueType val);
	void copy_variables(const std::unordered_map<std::string, ValuePtr>& from, std::unordered_map<std::string, ValuePtr>& whom);
}
#endif // !_OTHER_H_