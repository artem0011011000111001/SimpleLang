#include "AST.h"

using namespace Simple;

CaseStatement::CaseStatement(ExpressionPtr expr, StatementPtr statement, bool isDefault)
	: expr(std::move(expr)), statement(std::move(statement)), isDefault(isDefault) {}

void CaseStatement::execute() {
	if (statement)
		statement->execute();
}

ExpressionPtr CaseStatement::GetExpression() {
	return std::move(expr);
}

std::string CaseStatement::to_string() {
	if (isDefault) {
		return "default: " + statement->to_string();
	}
	else {
		return "case " + expr->to_string() + statement->to_string();
	}
}