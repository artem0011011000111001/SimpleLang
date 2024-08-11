#include "Expressions.h"
#include "Simple_defines.h"

using namespace Simple;

CharExpression::CharExpression(WString value)
	: value(value) {}

Value& CharExpression::eval() {
	ref = CHAR(value);
	return *ref;
}