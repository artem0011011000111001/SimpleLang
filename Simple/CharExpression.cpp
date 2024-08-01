#include "Expressions.h"
#include "Simple_defines.h"

using namespace Simple;

CharExpression::CharExpression(String value)
	: value(value) {}

Value& CharExpression::eval() {
	ref = CHAR(value);
	return *ref;
}