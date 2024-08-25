#include "Expressions.h"

using namespace Simple;

PercentExpression::PercentExpression(double value)
	: value(value) {}

Value& PercentExpression::eval() {
	ref = PERCENT(value);

	return *ref;
}
