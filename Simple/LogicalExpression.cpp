#include "Parser.h"
#include "Simple_Error.h"
#include "Expressions.h"

using namespace Simple;

ExpressionPtr Parser::expression() {
	return ternary();
}

ExpressionPtr Parser::ternary() {
	ExpressionPtr result = logicalOr();

	while (true)
	{
		if (match(TokenType::QUESTION)) {
			ExpressionPtr expr1 = logicalOr();

			consume(TokenType::COLON);

			ExpressionPtr expr2 = logicalOr();

			return CREATE_PTR<TernaryExpression>(MOVE(result), MOVE(expr1), MOVE(expr2));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::logicalOr() {
	ExpressionPtr result = logicalAnd();

	while (true)
	{
		if (match(TokenType::BARBAR)) {
			return CREATE_PTR<ConditionalExpression>(MOVE(result), LogicOperators::OR, MOVE(logicalAnd()));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::logicalAnd() {
	ExpressionPtr result = equality();

	while (true)
	{
		if (match(TokenType::AMPAMP)) {
			return CREATE_PTR<ConditionalExpression>(MOVE(result), LogicOperators::AND, MOVE(equality()));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::equality() {
	ExpressionPtr result = conditinal();
	while (true)
	{
		if (match(TokenType::EQEQ)) {
			return CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::EQUALS, std::move(conditinal()));
			continue;
		}
		if (match(TokenType::EXCLEQ)) {
			return CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::NOT_EQUALS, std::move(conditinal()));
			continue;
		}
		break;
	}

	return result;
}

ExpressionPtr Parser::conditinal() {
	ExpressionPtr result = additive();
	while (true)
	{
		if (match(TokenType::LT)) {
			result = CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::LT, std::move(additive()));
			continue;
		}
		else if (match(TokenType::LTEQ)) {
			result = CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::LTEQ, std::move(additive()));
			continue;
		}
		else if (match(TokenType::GT)) {
			result = CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::GT, std::move(additive()));
			continue;
		}
		else if (match(TokenType::GTEQ)) {
			result = CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::GTEQ, std::move(additive()));
			continue;
		}
		break;
	}
	return result;
}