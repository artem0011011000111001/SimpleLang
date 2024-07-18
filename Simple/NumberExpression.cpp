#include "Expressions.h"
#include "Values.h"

using namespace Simple;

NumberExpression::NumberExpression(const double value) : value(value) {}

ValuePtr NumberExpression::eval() const {
	return std::make_unique<NumberValue>(value);
}

std::string NumberExpression::to_string() const {
	return std::to_string(value);
}