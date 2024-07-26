#include "Expressions.h"
#include "Values.h"
#include "Simple_defines.h"

using namespace Simple;

StringExpression::StringExpression(std::string value) : value(value) {}

//ValuePtr StringExpression::eval() {
//	return get_ref().clone();
//}

Value& StringExpression::eval() {
	ref = STRING(value);
	return *ref;
}
