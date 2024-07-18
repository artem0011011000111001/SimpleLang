#include "Expressions.h"
#include "Values.h"
#include "Function.h"
#include "Functions.h"
#include "Variables.h"

using namespace Simple;


FunctionalExpression::FunctionalExpression(std::string name, std::vector<ExpressionPtr> args) 
	: name(name), args(std::move(args)) {}

ValuePtr FunctionalExpression::eval() const {
	std::vector<ValuePtr> values;
	values.reserve(args.size());

	for (const auto& arg : args) {
		values.push_back(arg->eval());
	}

	return Functions::Get(name)->execute(std::move(values));
}

void FunctionalExpression::AddArgument(ExpressionPtr arg) {
	args.push_back(std::move(arg));
}

std::string FunctionalExpression::to_string() const {
	return name + "(" + [this]() {
		std::string res;
		for (const auto& arg : args)
		{
			res += arg->to_string();
		}
		return res;
		}() + ");";
}