#pragma once

#ifndef _SIMPLE_TYPEDEFS_H_
#define _SIMPLE_TYPEDEFS_H_

#include <memory>

namespace Simple {
	class Value;
	class Expression;
	class Statement;
	class Function;

	using ValuePtr      = std::unique_ptr<Value>;
	using ExpressionPtr = std::unique_ptr<Expression>;
	using StatementPtr  = std::unique_ptr<Statement>;
	using FunctionPtr   = std::unique_ptr<Function>;
}
#endif // !_TYPEDEFS_H_