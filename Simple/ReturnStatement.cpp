#include "AST.h"

using namespace Simple;

ReturnStatement::ReturnStatement(ExpressionPtr expr) : expr(std::move(expr)) {}

void ReturnStatement::execute() {
	throw expr->eval().clone();
}

const ExpressionPtr& ReturnStatement::GetExpression() const {
	return expr;
}
