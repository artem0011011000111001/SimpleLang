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
	struct ArgParams;
	struct Field_decl;
	struct RawField_decl;
	struct FuncParams;

	enum class ValueType;

	using String			= std::string;
	using WString			= std::wstring;
	using WChar = wchar_t;
	template<class _PtrTy>
	using Ptr				= std::unique_ptr<_PtrTy>;
	template<class _KeyTy, class _ValTy>
	using Map				= std::unordered_map<_KeyTy, _ValTy>;
	template<class _ValTy>
	using Str_map			= Map<String, _ValTy>;
	template<class _ValTy>
	using WStr_map			= Map<WString, _ValTy>;
	template<class _Ty>
	using Vec				= std::vector<_Ty>;
	using Str_vec			= Vec<String>;
	using WStr_vec			= Vec<WString>;
	using ValuePtr			= Ptr<Value>;
	using ExpressionPtr		= Ptr<Expression>;
	using StatementPtr		= Ptr<Statement>;
	using FunctionPtr		= Ptr<Function>;
	using VALUE				= ValuePtr;
	using Val_map			= WStr_map<ValuePtr>;
	using Vars_t			= WStr_map<Variable>;
	using Funcs_t			= WStr_map<FuncParams>;
	using Fields_decl_t		= WStr_map<Field_decl>;
	using RawFields_decl_t  = WStr_map<RawField_decl>;
	using Structs_t			= WStr_map<Fields_decl_t>;
	using Args_t			= Vec<ValuePtr>;
	using ArgsParams_t		= Vec<ArgParams>;
	using Elements_t		= Args_t;
	using Field				= Variable;
	using Fields_t			= Vars_t;
}
#endif // _SIMPLE_TYPEDEFS_H_