#include "Expressions.h"
#include "Functions.h"

using namespace Simple;

FunctionExpression::FunctionExpression(WString& key)
	: key(key) {}

Value& FunctionExpression::eval() {
	//ref = FUNCTION(Functions::Get(key));
	return *ref;
}