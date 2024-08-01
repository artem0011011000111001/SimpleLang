#pragma once

#ifndef _SIMPLE_TYPEDEFS_H_
#define _SIMPLE_TYPEDEFS_H_

#include <memory>
#include <vector>
#include <utility>
#include <list>
#include <string>
#include <unordered_map>

namespace Simple {
	class Value;
	class Expression;
	class Statement;
	class Function;
	struct Variable;
	enum class ValueType;

	template<class _PtrTy>
	using Ptr			= std::unique_ptr<_PtrTy>;
	using String		= std::string;
	using Str_vec		= std::vector<String>;
	using ValuePtr      = Ptr<Value>;
	using ExpressionPtr = Ptr<Expression>;
	using StatementPtr  = Ptr<Statement>;
	using FunctionPtr   = Ptr<Function>;
	using VALUE			= ValuePtr;
	using Val_map		= std::unordered_map<String, ValuePtr>;
	using Vars_t		= std::unordered_map<String, Variable>;
	using Funcs_t		= std::unordered_map<String, FunctionPtr>;
	using Fields_decl_t = std::unordered_map<String, ValueType>;
	using Structs_t		= std::unordered_map<String, Fields_decl_t>;
	using Args_t		= std::vector<VALUE>;
	using ArgsParam_t   = std::pair<std::list<String>, std::list<bool>>;
}
#endif // _SIMPLE_TYPEDEFS_H_