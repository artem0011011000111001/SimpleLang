#include "AST.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

ConstAssigmentStatement::ConstAssigmentStatement(std::string variable, ExpressionPtr expression)
	: variable(variable), expression(std::move(expression)) {}

void ConstAssigmentStatement::execute() {
	if (variable == "true" || variable == "false")
		throw Simple_Error("You cannot use keywords to name variables");
	ValuePtr result = expression.get()->eval();
	Variables::Set(variable, Variable(std::move(result), true));
	//Variables::AddConstant(variable);
}

std::string ConstAssigmentStatement::to_string() {
	return "const" + variable + " = " + expression->eval()->AsString() + ";";
}