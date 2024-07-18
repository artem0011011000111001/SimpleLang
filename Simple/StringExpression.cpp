#include "Expressions.h"
#include "Values.h"

using namespace Simple;

StringExpression::StringExpression(const std::string value) : value(value) {}

ValuePtr StringExpression::eval() const {
	return std::make_unique<StringValue>(value);
}

std::string StringExpression::to_string() const {
	return value;
}