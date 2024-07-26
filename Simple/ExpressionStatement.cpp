#include "AST.h"

using namespace Simple;

ExpressionStatement::ExpressionStatement(ExpressionPtr expr) 
	: expr(std::move(expr)) {}

void ExpressionStatement::execute() {
	expr->eval();
}