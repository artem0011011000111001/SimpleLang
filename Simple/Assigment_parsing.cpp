#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

StatementPtr Parser::Assignment(bool IsConst) {
	Token CurrentToken = get(0);
	if (match(TokenType::WORD)) {

		const std::string variable = CurrentToken.getText();
		if (match(TokenType::EQ)) {

			ExpressionPtr result = expression();
			//CHECK_END_STR
			if (IsConst) return std::make_unique<ConstAssigmentStatement>(variable, std::move(result));

			else return std::make_unique<AssigmentStatement>(variable, std::move(result));
		}

		else if (match(TokenType::PLUSPLUS)) {

			//CHECK_END_STR
			if (IsConst) return std::make_unique<ConstAssigmentStatement>(variable, std::make_unique<UnaryExpression>("++i",
				std::make_unique<VariableExpression>(variable)));

			else return std::make_unique<AssigmentStatement>(variable, std::make_unique<UnaryExpression>("++i",
				std::make_unique<VariableExpression>(variable)));
		}

		else if (match(TokenType::MINUSMINUS)) {

			//CHECK_END_STR
			return std::make_unique<AssigmentStatement>(variable, std::make_unique<UnaryExpression>("--i",
				std::make_unique<VariableExpression>(variable)));
		}

		auto OPEREQ = [this, variable, IsConst](const BinaryOperators operation) -> StatementPtr {
			ExpressionPtr result = expression();
			//CHECK_END_STR
			if (IsConst) return std::make_unique<ConstAssigmentStatement>(variable,
				std::make_unique<BinaryExpression>(std::make_unique<VariableExpression>(variable), operation, std::move(result)));

			else return std::make_unique<AssigmentStatement>(variable,
				std::make_unique<BinaryExpression>(std::make_unique<VariableExpression>(variable), operation, std::move(result)));
			};

		if (match(TokenType::PLUSEQ))
			return OPEREQ(BinaryOperators::PLUS);


		else if (match(TokenType::MINUSEQ))
			return OPEREQ(BinaryOperators::MINUS);

		else if (match(TokenType::STAREQ))
			return OPEREQ(BinaryOperators::MULTIPLY);

		else if (match(TokenType::SLASHEQ))
			return OPEREQ(BinaryOperators::DIVIDE);

		else if (match(TokenType::STARSTAREQ))
			return OPEREQ(BinaryOperators::POWER);
	}

	else if (match(TokenType::PLUSPLUS) && get(0).getType() == TokenType::WORD) {

		StatementPtr result;

		if (IsConst) result = std::make_unique<ConstAssigmentStatement>(get(0).getText(),
			std::make_unique<UnaryExpression>("++i", std::move(primary())));

		else result = std::make_unique<AssigmentStatement>(get(0).getText(),
			std::make_unique<UnaryExpression>("++i", std::move(primary())));

		//CHECK_END_STR

		return result;
	}

	else if (match(TokenType::MINUSMINUS) && get(0).getType() == TokenType::WORD) {
		StatementPtr result;

		if (IsConst) result = std::make_unique<ConstAssigmentStatement>(get(0).getText(),
			std::make_unique<UnaryExpression>("--i", std::move(primary())));

		else result = std::make_unique<AssigmentStatement>(get(0).getText(),
			std::make_unique<UnaryExpression>("--i", std::move(primary())));

		//CHECK_END_STR

		return result;
	}
}

StatementPtr Parser::ConstAssignment() {
	return Assignment(true);
}