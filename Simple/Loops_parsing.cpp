#include "Parser.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::DoWhile() {
	StatementPtr statement = statementOrBlock();
	consume(TokenType::WHILE);
	consume(TokenType::LPAREN);
	ExpressionPtr condition = expression();
	consume(TokenType::RPAREN);
	return std::make_unique<DoWhileStatement>(
		std::move(condition),
		std::move(statement)
	);
}

StatementPtr Parser::While() {
	consume(TokenType::LPAREN);
	ExpressionPtr condition = expression();
	consume(TokenType::RPAREN);
	StatementPtr statement = statementOrBlock();
	return std::make_unique<WhileStatement>(
		std::move(condition),
		std::move(statement)
	);
}

StatementPtr Parser::For() {

	consume(TokenType::LPAREN);
	StatementPtr initialization;

	Token CurrentToken = get(0);
	std::string InitName;
	if (CurrentToken.getType() == TokenType::WORD) InitName = CurrentToken.getText();

	if (match(TokenType::CONST)) initialization = ConstAssignment();
	else initialization = Assignment();
	consume(TokenType::SEMICOLON);

	ExpressionPtr termination = expression();
	consume(TokenType::SEMICOLON);

	StatementPtr increment = Assignment();
	consume(TokenType::RPAREN);

	StatementPtr statement = statementOrBlock();

	return std::make_unique<ForStatement>(
		std::move(InitName),
		std::move(initialization),
		std::move(termination),
		std::move(increment),
		std::move(statement)
	);
}

StatementPtr Parser::Break() {
	StatementPtr result = std::make_unique<BreakStatement>();

	CHECK_END_STR;

	return result;
}

StatementPtr Parser::Continue() {
	StatementPtr result = std::make_unique<ContinueStatement>();

	CHECK_END_STR;

	return result;
}