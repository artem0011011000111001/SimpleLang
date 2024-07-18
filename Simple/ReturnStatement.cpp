#include "AST.h"

using namespace Simple;

ReturnStatement::ReturnStatement(ExpressionPtr expr) : expr(std::move(expr)) {}

void ReturnStatement::execute() {
	throw expr->eval();
}

const ExpressionPtr& ReturnStatement::GetExpression() const {
	return expr;
}

std::string ReturnStatement::to_string() {
	return "return " + expr->to_string() + ";";
}
