#include "Parser.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::DoWhile() {
	StatementPtr statement = statementOrBlock();

	consume(TokenType::WHILE);
	consume(TokenType::LPAREN);

	ExpressionPtr condition = expression();

	consume(TokenType::RPAREN);

	return CREATE_PTR<DoWhileStatement>(
		MOVE(condition),
		MOVE(statement)
	);
}

StatementPtr Parser::While() {

	consume(TokenType::LPAREN);

	ExpressionPtr condition = expression();

	consume(TokenType::RPAREN);

	StatementPtr statement = statementOrBlock();

	return CREATE_PTR<WhileStatement>(
		MOVE(condition),
		MOVE(statement)
	);
}

StatementPtr Parser::For() {

	consume(TokenType::LPAREN);
	StatementPtr initialization;

	Token CurrentToken = get(0);
	WString InitName;
	if (CurrentToken.getType() == TokenType::WORD) InitName = CurrentToken.getText();

	if (match(TokenType::CONST)) initialization = ConstVariableDefine();
	else initialization = VariableDefine();
	consume(TokenType::SEMICOLON);

	ExpressionPtr termination = expression();
	consume(TokenType::SEMICOLON);

	ExpressionPtr increment = expression();
	consume(TokenType::RPAREN);

	StatementPtr statement = statementOrBlock();

	return CREATE_PTR<ForStatement>(
		MOVE(InitName),
		MOVE(initialization),
		MOVE(termination),
		MOVE(increment),
		MOVE(statement)
	);
}

StatementPtr Parser::ForEach() {
	bool isConst = false;

	consume(TokenType::LPAREN);

	if (match(TokenType::CONST))
		isConst = true;
	WString name = consume(TokenType::WORD).getText();

	consume(TokenType::COLON);

	WString in = consume(TokenType::WORD).getText();

	consume(TokenType::RPAREN);

	StatementPtr block = statementOrBlock();

	return CREATE_PTR<ForEachStatement>(name, isConst, in, MOVE(block));
}

StatementPtr Parser::Break() {
	StatementPtr result = CREATE_PTR<BreakStatement>();

	CHECK_END_STR;

	return result;
}

StatementPtr Parser::Continue() {
	StatementPtr result = CREATE_PTR<ContinueStatement>();

	CHECK_END_STR;

	return result;
}