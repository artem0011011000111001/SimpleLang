#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "Simple_typedefs.h"
#include "Variable.h"
#include "Simple_defines.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace Simple {

	struct Variable;

	enum class ValueType {
		_DIGIT_,
		_NUMBER,
		_PERCENT,
		_CHAR,
		_STRING,
		_STRUCT,
		_VOID,
		_ARRAY,
		_FUNCTION,
		_CLASS
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
	void create_arguments(ArgsParams_t& argsParam, Args_t& args, bool is_any_args);
	void disassemble_arguments();
	void check_pos(int pos, int max_pos, const String& designator);
	String uni_to_ascii(const WString& str);
	Fields_decl_t copy_fields_params(const Fields_decl_t& from);
	FunctionPtr CheckAndGetFunc(const FuncParams& func, int argsCount);
	Vars_t to_vars_t(Fields_decl_t& other);
	Args_t copy_args(Args_t from);
	bool is_number_value(const ValuePtr& val);
	bool is_char_value(const ValuePtr& val);
	WString multiply_str(const WString& str, const int count);
	Vars_t copy_vars(const Vars_t& vars);
	Methods_t copy_methods(const Methods_t& methods);
	Args_t exprs_to_args(Vec<ExpressionPtr> exprs);

	void CreateDefaultFieldsValues(Fields_t& fields, Fields_decl_t& fields_params);

	Fields_decl_t RawToMade(RawFields_decl_t& raw);
	ClassFields_decl_t RawToMade(RawClassFields_decl_t& raw);
	//Methods_t RawToMade(RawMethod_decl_t raw, StatementPtr add_statement);


	std::function<VALUE(Args_t)> Statement_to_func(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args);
	std::function<VALUE(Args_t)> Statement_to_struct_constructor(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args, Fields_decl_t& fields_params, const WString& name);
	std::function<VALUE(Args_t)> Statement_to_class_constructor(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args, Fields_decl_t& fields_params, RawMethod_decl_t& methods_params, const WString& name);

	template<typename... Args>
	Args_t _HAND_OVER_ARGS(Args&&... args) {
		Args_t newArgs;

		(newArgs.push_back(std::forward<Args>(args)), ...);
		return MOVE(newArgs);
	}

	Fields_decl_t _DECL_FIELDS(std::initializer_list<PAIR<WString, Field_info>> fields);
}
#endif // _UTILS_H_