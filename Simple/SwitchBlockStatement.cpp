#include "AST.h"

using namespace Simple;

void SwitchBlockStatement::execute() {}

void SwitchBlockStatement::add(CaseStatement statement) {
	CaseStatements.push_back(std::move(statement));
}

/*CaseStatement Get(size_t pos) {
	auto it = CaseStatements.begin();
	std::advance(it, pos);
	return std::move(*it);
}*/

std::list<CaseStatement>& SwitchBlockStatement::getCaseStatements() {
	return CaseStatements;
}