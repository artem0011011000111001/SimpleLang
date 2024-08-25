#include "Parser.h"
#include "Utils.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::TryCatch() {
	StatementPtr tryBlock = statementOrBlock();

	Vec<StatementPtr> catchBlocks;
	WStr_vec keys;
	Vec<bool> isConsts;
	WStr_vec types_in_str;

	StatementPtr finally_block;

	consume(TokenType::CATCH);

	do {
		bool isConst = false;
		consume(TokenType::LPAREN);

		if (match(TokenType::CONST))
			isConst = true;

		isConsts.push_back(isConst);

		keys.push_back(consume(TokenType::WORD).getText());
		consume(TokenType::COLON);

		types_in_str.push_back(consume(TokenType::WORD).getText());

		consume(TokenType::RPAREN);

		catchBlocks.push_back(statementOrBlock());

	} while (match(TokenType::CATCH));

	if (match(TokenType::FINALLY))
		finally_block = statementOrBlock();

	return CREATE_PTR<TryCatchStatement>(MOVE(tryBlock), keys, isConsts, types_in_str, MOVE(catchBlocks), MOVE(finally_block));
}

StatementPtr Parser::Throw() {
	ExpressionPtr expr = expression();

	return CREATE_PTR<ThrowStatement>(std::move(expr));
}
