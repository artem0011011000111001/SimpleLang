#include "Expressions.h"
#include "Simple_defines.h"

using namespace Simple;

Value& VoidExpression::eval() {
	ref = VOID;

	return *ref;
}