#include "Parser.h"
#include "Simple_Error.h"
#include "Expressions.h"

using namespace Simple;

ExpressionPtr Parser::additive() {
	ExpressionPtr result = multiplicative();
	while (true)
	{
		if (match(TokenType::PLUS)) {
			result = CREATE_PTR<BinaryExpression>(std::move(result), BinaryOperators::PLUS, std::move(multiplicative()));
			continue;
		}
		else if (match(TokenType::MINUS)) {
			result = CREATE_PTR<BinaryExpression>(std::move(result), BinaryOperators::MINUS, std::move(multiplicative()));
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
			result = CREATE_PTR<BinaryExpression>(std::move(result), BinaryOperators::MULTIPLY, std::move(power()));
			continue;
		}
		else if (match(TokenType::SLASH)) {
			result = CREATE_PTR<BinaryExpression>(std::move(result), BinaryOperators::DIVIDE, std::move(power()));
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
			result = CREATE_PTR<BinaryExpression>(std::move(result), BinaryOperators::POWER, std::move(Unary()));
			continue;
		}
		break;
	}
	return result;
}

ExpressionPtr Parser::Unary() {

	if (match(TokenType::MINUS))
		return CREATE_PTR<UnaryExpression>("-", std::move(primary()));

	if (match(TokenType::PLUS))
		return primary();

	if (match(TokenType::EXCL))
		return CREATE_PTR<UnaryExpression>("!", std::move(primary()));

	if (match(TokenType::PLUSPLUS)) {
		return CREATE_PTR<UnaryExpression>("++i", std::move(primary()));
	}

	if (match(TokenType::MINUSMINUS)) {
		return CREATE_PTR<UnaryExpression>("--i", std::move(primary()));
	}

	ExpressionPtr expr = primary();

	if (match(TokenType::PLUSPLUS))
		return CREATE_PTR<UnaryExpression>("i++", std::move(expr));

	if (match(TokenType::MINUSMINUS))
		return CREATE_PTR<UnaryExpression>("i--", std::move(expr));

	ExpressionPtr result = std::move(expr);
	while (true) {
		if (match(TokenType::DOT)) {
			std::string field_name = consume(TokenType::WORD).getText();
			result = CREATE_PTR<StructExpression>(std::move(result), field_name);
		}

		else if (match(TokenType::LSBRACKET)) {
			ExpressionPtr pos = expression();
			consume(TokenType::RSBRACKET);

			result = CREATE_PTR<IndexExpression>(std::move(result), std::move(pos));
		}

		else break;
	}

	return result;
}

ExpressionPtr Parser::primary() {
	const Token CurrentToken = get(0);

	if (CurrentToken.getType() == TokenType::WORD) {
		Token NextToken = get(1);

		if (NextToken.getType() == TokenType::LPAREN)
			return Function();
	}

	/*if ((
		CurrentToken.getType() == TokenType::WORD ||
		CurrentToken.getType() == TokenType::TEXT ||
		CurrentToken.getType() == TokenType::HEX_NUMBER)
		&& !in_processing)
		if (get(1).getType() == TokenType::DOT)
			return Struct();
		else if (get(1).getType() == TokenType::LSBRACKET)
			return Index();*/

	if (match(TokenType::WORD)) {
		if (get(-1).getText() == "true")
			return CREATE_PTR<NumberExpression>(1);
		if (get(-1).getText() == "false")
			return CREATE_PTR<NumberExpression>(0);
		else
			return CREATE_PTR<VariableExpression>(CurrentToken.getText());
	}

	if (match(TokenType::NUMBER)) {
		double temp = std::stod(CurrentToken.getText());
		return CREATE_PTR<NumberExpression>(temp);
	}

	if (match(TokenType::HEX_NUMBER))
		return CREATE_PTR<NumberExpression>(stoihex(CurrentToken.getText()));

	if (match(TokenType::TEXT))
		return CREATE_PTR<StringExpression>(CurrentToken.getText());

	if (match(TokenType::LPAREN)) {
		ExpressionPtr result = expression();
		match(TokenType::RPAREN);
		return result;
	}

	else throw Simple_Error("Unknown expression");
}

ExpressionPtr Parser::Function() {
	std::string name = consume(TokenType::WORD).getText();
	consume(TokenType::LPAREN);

	FunctionalExpression function(name);
	while (!match(TokenType::RPAREN)) {
		function.AddArgument(expression());

		if (match(TokenType::COMMA) && (get(0).getType() == TokenType::RPAREN))
			throw Simple_Error("Expression required");
	}

	/*ExpressionPtr result = CREATE_PTR<FunctionalExpression>(std::move(function));
	while (true) {
		if (match(TokenType::DOT)) {
			std::string field_name = consume(TokenType::WORD).getText();
			result = CREATE_PTR<StructExpression>(std::move(result), field_name);
		}
		else if (match(TokenType::LSBRACKET)) {
			ExpressionPtr pos = expression();
			consume(TokenType::RSBRACKET);

			result = CREATE_PTR<IndexExpression>(std::move(result), std::move(pos));
		}
		else break;
	}*/
	return CREATE_PTR<FunctionalExpression>(std::move(function));
}