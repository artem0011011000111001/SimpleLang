#include "AST.h"

using namespace Simple;

DoWhileStatement::DoWhileStatement(ExpressionPtr expr, StatementPtr statement)
	: expr(std::move(expr)), statement(std::move(statement)) {}

void DoWhileStatement::execute() {
	do
	{
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
	} while (expr->eval()->AsDouble() != 0);
}

std::string DoWhileStatement::to_string() {
	return "do {\n" + statement->to_string() + "} while" + expr->to_string();
}