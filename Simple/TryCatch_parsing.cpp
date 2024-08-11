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

	WString key = consume(TokenType::WORD).getText();
	consume(TokenType::COLON);

	WString type_in_str = consume(TokenType::WORD).getText();

	consume(TokenType::RPAREN);

	StatementPtr catchBlock = statementOrBlock();

	return CREATE_PTR<TryCatchStatement>(MOVE(tryBlock), key, isConst, type_in_str, MOVE(catchBlock));
}

StatementPtr Parser::Throw() {
	ExpressionPtr expr = expression();

	return CREATE_PTR<ThrowStatement>(std::move(expr));
}
