#include "AST.h"

#include <iostream>

using namespace Simple;

PrintStatement::PrintStatement(ExpressionPtr expr) : expr(std::move(expr)) {}

void PrintStatement::execute() {
	std::cout << expr->eval()->AsString();
}

std::string Simple::PrintStatement::to_string() {
	return "print " + expr->eval()->AsString() + ";";
}
