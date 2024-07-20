#include "AST.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

AssigmentStatement::AssigmentStatement(std::string variable, ExpressionPtr expression) 
	: variable(variable), expression(std::move(expression)) {}

void AssigmentStatement::execute() {
	if (variable == "true" || variable == "false")
		throw Simple_Error("You cannot use keywords to name variables");
	ValuePtr result = expression.get()->eval();
	Variables::Set(variable, Variable(std::move(result), false));
}

std::string AssigmentStatement::to_string() {
	return variable + " = " + expression->eval()->AsString() + ";";
}