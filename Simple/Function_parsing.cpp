#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

FunctionDefineStatement Parser::FunctionDefine() {
	std::string name = consume(TokenType::WORD).getText();
	consume(TokenType::LPAREN);

	std::list<std::string> argsNames;

	while (!match(TokenType::RPAREN)) {
		argsNames.push_back(consume(TokenType::WORD).getText());

		if (match(TokenType::COMMA) && (get(0).getType() == TokenType::RPAREN))
			throw Simple_Error("Name required");
	}

	StatementPtr body = statementOrBlock();
	return FunctionDefineStatement(name, argsNames, std::move(body));
}

StatementPtr Parser::Return() {
	ExpressionPtr expr = expression();

	CHECK_END_STR;

	return std::make_unique<ReturnStatement>(std::move(expr));
}