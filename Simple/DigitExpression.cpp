#include "Expressions.h"
#include "Simple_defines.h"

using namespace Simple;

DigitExpression::DigitExpression(double value)
	: value(value) {}

Value& DigitExpression::eval() {
	ref = DIGIT(value);

	return *ref;
}