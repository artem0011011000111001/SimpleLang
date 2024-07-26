#include "Expressions.h"
#include "Values.h"
#include "Simple_defines.h"

using namespace Simple;

NumberExpression::NumberExpression(double value) : value(value) {}

//ValuePtr NumberExpression::eval() {
//	return get_ref().clone();
//}

Value& NumberExpression::eval() {
	ref = NUMBER(value);

	return *ref;
}