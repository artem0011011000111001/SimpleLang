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

	using String = std::string;
	template<class _PtrTy>
	using Ptr			= std::unique_ptr<_PtrTy>;
	template<class _KeyTy, class _ValTy>
	using Map			= std::unordered_map<_KeyTy, _ValTy>;
	template<class _ValTy>
	using Str_map		= Map<String, _ValTy>;
	template<class _Ty>
	using Vec			= std::vector<_Ty>;
	using Str_vec		= Vec<String>;
	using ValuePtr      = Ptr<Value>;
	using ExpressionPtr = Ptr<Expression>;
	using StatementPtr  = Ptr<Statement>;
	using FunctionPtr   = Ptr<Function>;
	using VALUE			= ValuePtr;
	using Val_map		= Str_map<ValuePtr>;
	using Vars_t		= Str_map<Variable>;
	using Funcs_t		= Str_map<FunctionPtr>;
	using Fields_decl_t = Str_map<ValueType>;
	using Structs_t		= Str_map<Fields_decl_t>;
	using Args_t		= Vec<ValuePtr>;
	using ArgsParam_t   = std::pair<std::list<String>, std::list<bool>>;
	using Elements_t	= Args_t;
}
#endif // _SIMPLE_TYPEDEFS_H_