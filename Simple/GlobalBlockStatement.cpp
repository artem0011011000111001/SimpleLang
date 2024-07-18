#include "AST.h"

using namespace Simple;

void GlobalBlockStatement::execute() {
	for (const auto& statement : statements)
	{
		if (statement)
			statement->execute();
	}
}

void GlobalBlockStatement::add(StatementPtr statement) {
	statements.push_back(std::move(statement));
}

std::string GlobalBlockStatement::to_string() {
	std::string result;
	for (const auto& statement : statements)
	{
		result += statement->to_string() + "\n";
	}
	return result;
}