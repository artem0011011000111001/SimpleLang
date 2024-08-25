#include "Expressions.h"
#include "Functions.h"
#include "AST.h"
#include "ArgParams.h"

using namespace Simple;

InsideFunctionExpression::InsideFunctionExpression(ArgsParams_t argsParam, StatementPtr body, bool is_any_args)
	: argsParam(MOVE(argsParam)), body(MOVE(body)), is_any_args(is_any_args) {}

Value& InsideFunctionExpression::eval() {

	Map<int, FunctionPtr> func_;
	func_.emplace((int)argsParam.size(), MOVE(Functions::CreateDynamicFunction(Statement_to_func(body, argsParam, is_any_args))));

	ref = FUNCTION(MOVE(func_));
	return *ref;
}
