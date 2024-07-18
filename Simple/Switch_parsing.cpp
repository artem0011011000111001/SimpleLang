#include "Parser.h"
#include "Simple_Error.h"

using namespace Simple;

StatementPtr Parser::Switch() {

	consume(TokenType::LPAREN);
	ExpressionPtr expr = expression();

	consume(TokenType::RPAREN);
	SwitchBlockStatement block = switchBlock();

	return std::make_unique<SwitchStatement>(std::move(expr), std::move(block));
}

CaseStatement Parser::caseStatement() {
	ExpressionPtr expr;
	bool isDefault = false;

	if (!match(TokenType::CASE)) {
		if (match(TokenType::DEFAULT)) {
			expr = nullptr;
			isDefault = true;
		}
		else throw Simple_Error("Expected case or default");
	}
	else
		expr = expression();

	StatementPtr statement = statementOrBlock();

	return CaseStatement(std::move(expr), std::move(statement), isDefault);
}