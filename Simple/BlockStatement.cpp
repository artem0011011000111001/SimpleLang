#include "AST.h"
#include "Variables.h"
#include "Utils.h"

using namespace Simple;

void BlockStatement::execute() {
	//const auto& CurrentVariables = Variables::GetAllVariables();
	//std::unordered_map<std::string, ValuePtr> VariablesBefore;

	/*for (auto& var : CurrentVariables)
	{
		VariablesBefore[var.first] = var.second->clone();
	}*/
	//std::unordered_map<std::string, ValuePtr> VariablesBefore;
	//copy_variables(Variables::GetAllVariables(), VariablesBefore);

	for (const auto& statement : statements)
	{
		if (statement)
			statement->execute();
	}

	//Variables::SetAllVariables(std::move(VariablesBefore));
}

void BlockStatement::add(StatementPtr statement) {
	statements.push_back(std::move(statement));
}