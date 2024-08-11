#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "Simple_typedefs.h"
#include "Variable.h"
#include "Simple_defines.h"

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
		_FUNCTION
		//_USER_STRUCT
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

	Val_map CreateTypedDefaultValue();

	double strict_stod(const WString str);
	String to_string(LogicOperators op);
	String to_string(BinaryOperators op);
	WString IdentifyCategory(ValueType type);
	ValueType IdentifyValueType(const WString& key);
	bool equals_type(const WString& key1, const WString& key2);
	void copy_variables(const Vars_t& from, Vars_t& whom);
	void create_arguments(ArgsParams_t& argsParam, Args_t& args, Vars_t& whom, bool is_any_args);
	void disassemble_arguments(Vars_t &from);
	void check_pos(int pos, int max_pos, const String& designator);
	Fields_decl_t copy_fields_params(const Fields_decl_t& from);
	FunctionPtr CheckAndGetFunc(const FuncParams& func, int argsCount);
}
#endif // _UTILS_H_