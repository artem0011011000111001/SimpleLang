#include "Parser.h"
#include "Utils.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::TryCatch() {
	bool isConst = false;
	StatementPtr tryBlock = statementOrBlock();

	consume(TokenType::CATCH);
	consume(TokenType::LPAREN);

	if (match(TokenType::CONST))
		isConst = true;

	String key = consume(TokenType::WORD).getText();
	consume(TokenType::COLON);

	String type_in_str = consume(TokenType::WORD).getText();

	consume(TokenType::RPAREN);

	StatementPtr catchBlock = statementOrBlock();

	return CREATE_PTR<TryCatchStatement>(std::move(tryBlock), key, isConst, type_in_str, std::move(catchBlock));
}

StatementPtr Parser::Throw() {
	ExpressionPtr expr = expression();

	return CREATE_PTR<ThrowStatement>(std::move(expr));
}
