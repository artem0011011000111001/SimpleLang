#include "AST.h"
#include "Variables.h"

using namespace Simple;

WhileStatement::WhileStatement(ExpressionPtr expr, StatementPtr statement) 
	: expr(std::move(expr)), statement(std::move(statement)) {}

void WhileStatement::execute() {
	Variables::PushState();
	while (expr->eval()->AsDouble() != 0) {
		try {
			statement->execute();
		}
		catch (const BreakStatement&) {
			break;
		}
		catch (const ContinueStatement&) {
			//continue;
		}
	}
	Variables::PopState();
}

std::string WhileStatement::to_string() {
	return "while " + expr->to_string() + " {\n" + statement->to_string() + "}";
}