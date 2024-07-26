#include "Expressions.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Variables.h"

using namespace Simple;

VariableExpression::VariableExpression(const std::string& name) : name(name) {}

//ValuePtr VariableExpression::eval() {
//	return get_ref().clone();
//}

Value& VariableExpression::eval() {
	if (!Variables::IsExist(name)) throw Simple_Error("\"" + name + "\" not defined");
	return Variables::GetRef(name);
}