#include "Expressions.h"
#include "Values.h"
#include "Function.h"
#include "Functions.h"
#include "Variable.h"
#include "Variables.h"

using namespace Simple;


FunctionalExpression::FunctionalExpression(String name, std::vector<ExpressionPtr> args)
	: name(name), args(std::move(args)) {}

Value& FunctionalExpression::eval() {
	Args_t values;
	values.reserve(args.size());

	for (const auto& arg : args) {
		values.push_back(arg->eval().clone());
	}

	ref = Functions::Get(name)->execute(std::move(values));
	return *ref;
}

void FunctionalExpression::AddArgument(ExpressionPtr arg) {
	args.push_back(std::move(arg));
}