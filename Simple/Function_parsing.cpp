#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "ArgParams.h"

using namespace Simple;

void Parser::AnalyzeFunction(ArgsParams_t& argsParams, StatementPtr& body, bool& is_any_args) {
	consume(TokenType::LPAREN);

	while (!match(TokenType::RPAREN)) {
		ArgParams currentArgParam;

		if (match(TokenType::CONST)) currentArgParam.isConst = true;
		else currentArgParam.isConst = false;

		currentArgParam.name = consume(TokenType::WORD).getText();

		if (match(TokenType::STAR)) {
			is_any_args = true;
			consume(TokenType::RPAREN);
			argsParams.push_back(MOVE(currentArgParam));
			break;
		}

		else if (match(TokenType::EQ))
			currentArgParam.defaultValue = MOVE(expression());

		argsParams.push_back(MOVE(currentArgParam));

		if (match(TokenType::RPAREN))
			break;

		consume(TokenType::COMMA);
	}

	body = statementOrBlock();
}

StatementPtr Parser::FunctionDefine() {

	WString name = consume(TokenType::WORD).getText();
	ArgsParams_t argsParam;
	StatementPtr body;
	bool is_any_args = false;

	AnalyzeFunction(argsParam, body, is_any_args);

	return CREATE_PTR<FunctionDefineStatement>(name, MOVE(argsParam), MOVE(body), is_any_args);
}

StatementPtr Parser::Return() {
	ExpressionPtr expr = expression();

	CHECK_END_STR;

	return CREATE_PTR<ReturnStatement>(MOVE(expr));
}