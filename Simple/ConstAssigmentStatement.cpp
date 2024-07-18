#include "AST.h"
#include "Variables.h"

using namespace Simple;

ConstAssigmentStatement::ConstAssigmentStatement(std::string variable, ExpressionPtr expression)
	: variable(variable), expression(std::move(expression)) {}

void ConstAssigmentStatement::execute() {
	ValuePtr result = expression.get()->eval();
	Variables::Set(variable, std::move(result));
	Variables::AddConstant(variable);
}

std::string ConstAssigmentStatement::to_string() {
	return "const" + variable + " = " + expression->eval()->AsString() + ";";
}