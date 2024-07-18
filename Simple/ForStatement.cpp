#include "AST.h"

using namespace Simple;

ForStatement::ForStatement(StatementPtr initialization, ExpressionPtr termination,
	StatementPtr increment, StatementPtr block) 
	: initialization(std::move(initialization)), termination(std::move(termination)),
	increment(std::move(increment)), statement(std::move(block)) {}

void ForStatement::execute() {
	for (initialization->execute();
		termination->eval()->AsDouble() != 0;
		increment->execute()) {
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

std::string ForStatement::to_string() {
	return "for " + initialization->to_string() + ", " + termination->to_string() + ", " + 
		increment->to_string() + " {\n" + statement->to_string() + "}";
}