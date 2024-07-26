#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

StatementPtr Parser::FunctionDefine() {
	std::string name = consume(TokenType::WORD).getText();
	consume(TokenType::LPAREN);

	std::pair<std::list<std::string>, std::list<bool>> argsParam;

	while (!match(TokenType::RPAREN)) {
		if (match(TokenType::CONST))
			argsParam.second.push_back(true);
		else
			argsParam.second.push_back(false);
		argsParam.first.push_back(consume(TokenType::WORD).getText());

		if (match(TokenType::COMMA) && (get(0).getType() == TokenType::RPAREN))
			throw Simple_Error("Name required");
	}

	StatementPtr body = statementOrBlock();
	return CREATE_PTR<FunctionDefineStatement>(name, argsParam, std::move(body));
}

StatementPtr Parser::Return() {
	ExpressionPtr expr = expression();

	CHECK_END_STR;

	return std::make_unique<ReturnStatement>(std::move(expr));
}