#include "Parser.h"
#include "Simple_Error.h"
#include "Expressions.h"

using namespace Simple;

ExpressionPtr Parser::expression() {
	return logicalOr();
}

ExpressionPtr Parser::logicalOr() {
	ExpressionPtr result = logicalAnd();

	while (true)
	{
		if (match(TokenType::BARBAR)) {
			return CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::OR, std::move(logicalAnd()));
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
			return CREATE_PTR<ConditionalExpression>(std::move(result), LogicOperators::AND, std::move(equality()));
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