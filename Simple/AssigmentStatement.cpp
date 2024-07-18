#include "AST.h"
#include "Variables.h"

using namespace Simple;

AssigmentStatement::AssigmentStatement(std::string variable, ExpressionPtr expression) 
	: variable(variable), expression(std::move(expression)) {}

void AssigmentStatement::execute() {
	ValuePtr result = expression.get()->eval();
	Variables::Set(variable, std::move(result));
}

std::string AssigmentStatement::to_string() {
	return variable + " = " + expression->eval()->AsString() + ";";
}