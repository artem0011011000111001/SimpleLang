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

	ExpressionPtr result;

	if (match(TokenType::MINUS))
		result = CREATE_PTR<UnaryExpression>(UnaryOperators::MINUS, std::move(primary()));

	else if (match(TokenType::PLUS))
		result = primary();

	else if (match(TokenType::EXCL))
		result = CREATE_PTR<UnaryExpression>(UnaryOperators::NOT, std::move(primary()));

	else if (match(TokenType::PLUSPLUS)) {
		result = CREATE_PTR<UnaryExpression>(UnaryOperators::PRE_INC, std::move(primary()));
	}

	else if (match(TokenType::MINUSMINUS)) {
		result = CREATE_PTR<UnaryExpression>(UnaryOperators::PRE_DEC, std::move(primary()));
	}

	else result = primary();

	while (true) {
		if (match(TokenType::DOT)) {
			String field_name = consume(TokenType::WORD).getText();
			result = CREATE_PTR<StructExpression>(std::move(result), field_name);
		}

		else if (match(TokenType::LSBRACKET)) {
			ExpressionPtr pos = expression();
			consume(TokenType::RSBRACKET);

			result = CREATE_PTR<IndexExpression>(std::move(result), std::move(pos));
		}

		else if (match(TokenType::PLUSPLUS))
			result = CREATE_PTR<UnaryExpression>(UnaryOperators::POST_INC, std::move(result));

		else if (match(TokenType::MINUSMINUS))
			result = CREATE_PTR<UnaryExpression>(UnaryOperators::POST_DEC, std::move(result));

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

	if (match(TokenType::WORD)) {
		if (get(-1).getText() == "true")
			return CREATE_PTR<NumberExpression>(1);
		else if (get(-1).getText() == "false")
			return CREATE_PTR<NumberExpression>(0);
		else if (get(-1).getText() == "void")
			return CREATE_PTR<VoidExpression>();
		else
			return CREATE_PTR<VariableExpression>(CurrentToken.getText());
	}

	if (match(TokenType::NUM))
		return CREATE_PTR<NumberExpression>(std::stod(CurrentToken.getText()));

	if (match(TokenType::DIGIT_))
		return CREATE_PTR<DigitExpression>(std::stod(CurrentToken.getText()));

	if (match(TokenType::HEX_NUM))
		return CREATE_PTR<NumberExpression>(stoihex(CurrentToken.getText()));

	if (match(TokenType::TEXT))
		return CREATE_PTR<StringExpression>(CurrentToken.getText());

	if (match(TokenType::CHAR_))
		return CREATE_PTR<CharExpression>(CurrentToken.getText());

	if (match(TokenType::LPAREN)) {
		ExpressionPtr result = expression();
		match(TokenType::RPAREN);
		return result;
	}

	if (match(TokenType::LBRACE)) {
		Vec<ExpressionPtr> elements;
		while (!match(TokenType::RBRACE)) {
			elements.push_back(expression());
			match(TokenType::COMMA);
		}
		return CREATE_PTR<ArrayExpression>(std::move(elements));
	}

	else throw Simple_Error("Unknown expression");
}

ExpressionPtr Parser::Function() {
	String name = consume(TokenType::WORD).getText();
	consume(TokenType::LPAREN);

	FunctionalExpression function(name);
	while (!match(TokenType::RPAREN)) {
		function.AddArgument(expression());

		if (match(TokenType::COMMA) && (get(0).getType() == TokenType::RPAREN))
			throw Simple_Error("Expression required");
	}

	return CREATE_PTR<FunctionalExpression>(std::move(function));
}