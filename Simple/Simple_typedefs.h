#pragma once

#ifndef _SIMPLE_TYPEDEFS_H_
#define _SIMPLE_TYPEDEFS_H_

#include <memory>
#include <vector>

namespace Simple {
	class Value;
	class Expression;
	class Statement;
	class Function;

	template<class _PtrTy>
	using Ptr			= std::unique_ptr<_PtrTy>;
	using ValuePtr      = Ptr<Value>;
	using ExpressionPtr = Ptr<Expression>;
	using StatementPtr  = Ptr<Statement>;
	using FunctionPtr   = Ptr<Function>;
	using Args_t		= std::vector<ValuePtr>;
	using VALUE			= ValuePtr;
}
#endif // !_TYPEDEFS_H_