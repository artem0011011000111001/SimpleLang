#include "Parser.h"
#include "Simple_Error.h"
#include "Expressions.h"

using namespace Simple;

ExpressionPtr Parser::additive() {
	ExpressionPtr result = multiplicative();
	while (true)
	{
		if (match(TokenType::PLUS)) {
			result = std::make_unique<BinaryExpression>(std::move(result), BinaryOperators::PLUS, std::move(multiplicative()));
			continue;
		}
		else if (match(TokenType::MINUS)) {
			result = std::make_unique<BinaryExpression>(std::move(result), BinaryOperators::MINUS, std::move(multiplicative()));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::multiplicative() {
	ExpressionPtr result = power();
	while (true)
	{
		if (match(TokenType::STAR)) {
			result = std::make_unique<BinaryExpression>(std::move(result), BinaryOperators::MULTIPLY, std::move(power()));
			continue;
		}
		else if (match(TokenType::SLASH)) {
			result = std::make_unique<BinaryExpression>(std::move(result), BinaryOperators::DIVIDE, std::move(power()));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::power() {
	ExpressionPtr result = Unary();
	while (true)
	{
		if (match(TokenType::STARSTAR)) {
			result = std::make_unique<BinaryExpression>(std::move(result), BinaryOperators::POWER, std::move(Unary()));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::Unary() {

	if (match(TokenType::MINUS))
		return std::make_unique<UnaryExpression>("-", std::move(primary()));

	if (match(TokenType::PLUS))
		return primary();

	if (match(TokenType::EXCL))
		return std::make_unique<UnaryExpression>("!", std::move(primary()));


	if (match(TokenType::PLUSPLUS)) {

		if (get(0).getType() == TokenType::WORD)
			return std::make_unique<UnaryExpression>("++i", std::move(primary()));

		else throw Simple_Error("there must be a variable after the increment");
	}

	if (match(TokenType::MINUSMINUS)) {

		if (get(0).getType() == TokenType::WORD)
			return std::make_unique<UnaryExpression>("--i", std::move(primary()));

		else throw Simple_Error("there must be a variable after the decrement");
	}

	ExpressionPtr expr = primary();

	if (match(TokenType::PLUSPLUS))
		return std::make_unique<UnaryExpression>("i++", std::move(expr));

	if (match(TokenType::MINUSMINUS))
		return std::make_unique<UnaryExpression>("i--", std::move(expr));

	return expr;
}

ExpressionPtr Parser::primary() {
	const Token CurrentToken = get(0);
	if (match(TokenType::NUMBER))
		return std::make_unique<NumberExpression>(std::stod(CurrentToken.getText()));

	if (match(TokenType::HEX_NUMBER))
		return std::make_unique<NumberExpression>(stoihex(CurrentToken.getText()));

	if (get(0).getType() == TokenType::WORD && get(1).getType() == TokenType::LPAREN)
		return std::make_unique<FunctionalExpression>(std::move(Function()));

	if (match(TokenType::WORD)) {
		if (get(-1).getText() == "true")
			return std::make_unique<NumberExpression>(1);
		if (get(-1).getText() == "false")
			return std::make_unique<NumberExpression>(0);
		else 
			return std::make_unique<VariableExpression>(CurrentToken.getText());
	}

	if (match(TokenType::TEXT))
		return std::make_unique<StringExpression>(CurrentToken.getText());

	if (match(TokenType::LPAREN)) {
		ExpressionPtr result = expression();
		match(TokenType::RPAREN);
		return result;
	}

	else throw Simple_Error("Unknown expression");
}

FunctionalExpression Parser::Function() {
	std::string name = consume(TokenType::WORD).getText();
	consume(TokenType::LPAREN);

	FunctionalExpression function(name);
	while (!match(TokenType::RPAREN)) {
		function.AddArgument(expression());

		if (match(TokenType::COMMA) && (get(0).getType() == TokenType::RPAREN))
			throw Simple_Error("Expression required");
	}
	return function;
}