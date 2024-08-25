#include "Expressions.h"

using namespace Simple;

MethodExpression::MethodExpression(ExpressionPtr key, const WString& name, Vec<ExpressionPtr> args)
	: key(MOVE(key)), name(name), args(MOVE(args)) {}

Value& MethodExpression::eval() {
	Args_t values = exprs_to_args(MOVE(args));

	ref = key->eval().call_method(name, (int)values.size(), MOVE(values));

	return *ref;
}

void MethodExpression::AddArgument(ExpressionPtr arg) {
	args.push_back(MOVE(arg));
}