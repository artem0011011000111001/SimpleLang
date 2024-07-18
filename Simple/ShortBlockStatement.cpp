#include "AST.h"
#include "Variables.h"
#include "Utils.h"

using namespace Simple;

ShortBlockStatement::ShortBlockStatement(StatementPtr statement) 
	: statement(std::move(statement)) {}

void ShortBlockStatement::execute() {
	std::unordered_map<std::string, ValuePtr> VariablesBefore;
	copy_variables(Variables::GetAllVariables(), VariablesBefore);

	statement->execute();

	Variables::SetAllVariables(std::move(VariablesBefore));
}

std::string ShortBlockStatement::to_string() {
	return statement->to_string();
}