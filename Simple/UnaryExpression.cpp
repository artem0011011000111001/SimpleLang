#include "Expressions.h"
#include "Values.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

UnaryExpression::UnaryExpression(const std::string operation, ExpressionPtr expr) : operation(operation), expr(std::move(expr)) {}

ValuePtr UnaryExpression::eval() const {
	if (operation == "+")
		return std::make_unique<NumberValue>(expr->eval()->AsDouble());

	if (operation == "-")
		return std::make_unique<NumberValue>(-expr->eval()->AsDouble());

	if (operation == "!")
		return std::make_unique<NumberValue>(!(expr->eval()->AsDouble()));

	auto IncrementDecrement = [this](bool IsInc, bool IsPr) {
		std::string key = expr->to_string();
		if (Variables::IsExist(key)) {

			double value = Variables::Get(key)->AsDouble();
			double newValue = IsInc ? value + 1 : value - 1;

			Variables::Set(key, Variable(std::make_unique<NumberValue>(newValue), Variables::IsConstant(key)));
			return std::make_unique<NumberValue>(IsPr ? newValue : value);

		}
		return std::make_unique<NumberValue>(expr->eval()->AsDouble());
		};

	if (operation == "++i") {
		return IncrementDecrement(true, true);
	}

	if (operation == "i++") {
		return IncrementDecrement(true, false);
	}

	if (operation == "--i") {
		return IncrementDecrement(false, true);
	}

	if (operation == "i--") {
		return IncrementDecrement(false, false);
	}

	else throw Simple_Error("Unknown unary operation");
}

std::string UnaryExpression::to_string() const {
	return operation + expr.get()->eval().get()->AsString();
}