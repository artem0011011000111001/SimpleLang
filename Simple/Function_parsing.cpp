#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

void Parser::AnalyzeFunction(ArgsParam_t& argsParam, StatementPtr& body) {
	consume(TokenType::LPAREN);

	while (!match(TokenType::RPAREN)) {
		if (match(TokenType::CONST))
			argsParam.second.push_back(true);
		else
			argsParam.second.push_back(false);
		argsParam.first.push_back(consume(TokenType::WORD).getText());

		if (match(TokenType::COMMA) && (get(0).getType() == TokenType::RPAREN))
			throw Simple_Error("Name required");
	}

	body = statementOrBlock();
}

StatementPtr Parser::FunctionDefine() {

	String name = consume(TokenType::WORD).getText();
	ArgsParam_t argsParam;
	StatementPtr body;

	AnalyzeFunction(argsParam, body);

	return CREATE_PTR<FunctionDefineStatement>(name, argsParam, std::move(body));
}

StatementPtr Parser::Return() {
	ExpressionPtr expr = expression();

	CHECK_END_STR;

	return CREATE_PTR<ReturnStatement>(std::move(expr));
}