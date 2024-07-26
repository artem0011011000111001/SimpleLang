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