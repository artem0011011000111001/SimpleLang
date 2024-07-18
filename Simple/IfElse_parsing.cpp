#include "Parser.h"

using namespace Simple;

StatementPtr Parser::IfElse() {
	consume(TokenType::LPAREN);
	ExpressionPtr condition = expression();
	consume(TokenType::RPAREN);
	StatementPtr ifStatement = statementOrBlock();
	StatementPtr elseStatement;
	if (match(TokenType::ELSE)) elseStatement = statementOrBlock();
	else elseStatement = nullptr;

	StatementPtr result = std::make_unique<IfStatement>(
		std::move(condition), std::move(ifStatement),
		std::move(elseStatement)
	);
	return result;
}