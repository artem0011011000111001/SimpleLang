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

	double strict_stod(const String str);
	String to_string(LogicOperators op);
	String to_string(BinaryOperators op);
	String IdentifyCategory(ValueType type);
	ValueType IdentifyValueType(const String& key);
	bool equals_type(const String& key1, const String& key2);
	void copy_variables(const std::unordered_map<String, Variable>& from, std::unordered_map<String, Variable>& whom);
	void create_arguments(ArgsParam_t& argsParam, Args_t& args, std::unordered_map<String, Variable>& whom);
	void disassemble_arguments(std::unordered_map<String, Variable> &from);
	void check_pos(int pos, int max_pos, const String& designator);
}
#endif // _UTILS_H_