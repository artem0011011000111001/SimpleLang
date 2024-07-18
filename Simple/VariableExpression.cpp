#include "Expressions.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Variables.h"

using namespace Simple;

VariableExpression::VariableExpression(const std::string& name) : name(name) {}

ValuePtr VariableExpression::eval() const {
	if (!Variables::IsExist(name)) throw Simple_Error("\"" + name + "\" not defined");
	return Variables::Get(name);
}

std::string VariableExpression::to_string() const {
	return name;
}