#include "AST.h"

using namespace Simple;

WhileStatement::WhileStatement(ExpressionPtr expr, StatementPtr statement) 
	: expr(std::move(expr)), statement(std::move(statement)) {}

void WhileStatement::execute() {
	while (expr->eval()->AsDouble() != 0) {
		try
		{
			statement->execute();
		}
		catch (const BreakStatement&) {
			break;
		}
		catch (const ContinueStatement&) {
			//continue;
		}
	}
}

std::string WhileStatement::to_string() {
	return "while " + expr->to_string() + " {\n" + statement->to_string() + "}";
}