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
		_DIGIT_,
		_NUMBER,
		_CHAR,
		_STRING,
		_STRUCT,
		_VOID,
		_ARRAY,
		_USER_STRUCT
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

	enum class UnaryOperators {
		NOT,
		MINUS,
		PRE_INC,
		POST_INC,
		PRE_DEC,
		POST_DEC,
	};

	double strict_stod(const std::string str);
	std::string to_string(LogicOperators op);
	std::string to_string(BinaryOperators op);
	std::string IdentifyCategory(ValueType type);
	ValueType IdentifyValueType(const String& key);
	bool equals_type(const String& key1, const String& key2);
	void copy_variables(const std::unordered_map<std::string, Variable>& from, std::unordered_map<std::string, Variable>& whom);
	void create_arguments(ArgsParam_t& argsParam, Args_t& args, std::unordered_map<std::string, Variable>& whom);
	void disassemble_arguments(std::unordered_map<std::string, Variable> &from);
	void check_pos(int pos, int max_pos, const std::string& designator);
}
#endif // _UTILS_H_