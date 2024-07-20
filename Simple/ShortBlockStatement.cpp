#include "AST.h"
#include "Variables.h"
#include "Utils.h"

using namespace Simple;

ShortBlockStatement::ShortBlockStatement(StatementPtr statement) 
	: statement(std::move(statement)) {}

void ShortBlockStatement::execute() {
	statement->execute();
}

std::string ShortBlockStatement::to_string() {
	return statement->to_string();
}