#include "AST.h"
#include "Variables.h"

using namespace Simple;

IfStatement::IfStatement(ExpressionPtr expr, StatementPtr ifStatement, StatementPtr elseStatement) 
	: expr(std::move(expr)), ifStatement(std::move(ifStatement)), elseStatement(std::move(elseStatement)) {}

void IfStatement::execute() {
	double result = expr->eval()->AsDouble();
	
	Variables::PushState();
	if (result != 0) {
		elseStatement = nullptr;
		ifStatement->execute();
	}
	else if (elseStatement) elseStatement->execute();
	Variables::PopState();
}

std::string IfStatement::to_string() {
	return "if " + expr->eval()->AsString() + " {\n" + ifStatement->to_string() + "}" + 
		(elseStatement ? "\nelse {\n" + elseStatement->to_string() + "}" : "");
}