#include "Parser.h"
#include "Simple_Error.h"
#include "Expressions.h"
#include "Functions.h"
#include "ArgParams.h"

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
			WString name = consume(TokenType::WORD).getText();

			if (match(TokenType::LPAREN))
				result = Method(MOVE(result), name);

			else result = CREATE_PTR<FieldExpression>(MOVE(result), name);
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

	if (match(TokenType::FUNC))
		return InsideFunc();

	if (match(TokenType::_TRUE))
		return CREATE_PTR<NumberExpression>(1);

	if (match(TokenType::_FALSE))
		return CREATE_PTR<NumberExpression>(0);

	if (match(TokenType::_VOID_))
		return CREATE_PTR<VoidExpression>();

	if (match(TokenType::WORD))
		return CREATE_PTR<WordExpression>(CurrentToken.getText());

	if (match(TokenType::NUM))
		return CREATE_PTR<NumberExpression>(std::stod(CurrentToken.getText()));

	if (match(TokenType::DIGIT_))
		return CREATE_PTR<DigitExpression>(std::stod(CurrentToken.getText()));

	if (match(TokenType::HEX_NUM))
		return CREATE_PTR<NumberExpression>(stoihex(CurrentToken.getText()));

	if (match(TokenType::_PERCENT))
		return CREATE_PTR<PercentExpression>(std::stod(CurrentToken.getText()));

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

template<class _Ty>
inline void Parser::AnalyzeArgs(_Ty& f) {

	while (true) {

		ExpressionPtr expr;

		if (match(TokenType::RPAREN)) {
			expr = EXPR_DEFAULT;
			break;
		}

		else if (get(0).getType() == TokenType::COMMA)
			expr = EXPR_DEFAULT;

		else expr = expression();

		f.AddArgument(MOVE(expr));

		if (match(TokenType::RPAREN))
			break;

		consume(TokenType::COMMA);
	}

}

ExpressionPtr Parser::Function() {

	WString name = consume(TokenType::WORD).getText();
	consume(TokenType::LPAREN);

	CallFunctionExpression function(name);
	AnalyzeArgs(function);
	/*while (true) {

		ExpressionPtr expr;

		if (match(TokenType::RPAREN)) {
			expr = EXPR_DEFAULT;
			break;
		}

		else if (get(0).getType() == TokenType::COMMA)
			expr = EXPR_DEFAULT;

		else expr = expression();

		function.AddArgument(MOVE(expr));

		if (match(TokenType::RPAREN))
			break;
		
		consume(TokenType::COMMA);
	}*/

	return CREATE_PTR<CallFunctionExpression>(MOVE(function));
}

ExpressionPtr Parser::Method(ExpressionPtr expr, const WString& name) {

	MethodExpression method(MOVE(expr), name);

	AnalyzeArgs(method);

	return CREATE_PTR<MethodExpression>(MOVE(method));
}

ExpressionPtr Parser::InsideFunc() {
	ArgsParams_t argsParam;
	StatementPtr body;
	bool is_any_args = false;

	AnalyzeFunction(argsParam, body, is_any_args);

	return CREATE_PTR<InsideFunctionExpression>(MOVE(argsParam), MOVE(body), is_any_args);
}