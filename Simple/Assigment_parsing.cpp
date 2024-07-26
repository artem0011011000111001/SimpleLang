#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

StatementPtr Parser::Assignment(ExpressionPtr expr) {
	Token CurrentToken = get(0);

	if (match(TokenType::EQ)) {

		ExpressionPtr result = expression();

		return CREATE_PTR<AssigmentStatement>(std::move(expr), std::move(result));
	}

	auto OPEREQ = [this, &expr](const BinaryOperators operation) -> StatementPtr {
		ExpressionPtr result = expression();

		/*if (IsConst) 
			return CREATE_PTR<ConstAssigmentStatement>(std::move(expr),
				CREATE_PTR<BinaryExpression>(std::move(expr), operation, std::move(result)));

		else return CREATE_PTR<AssigmentStatement>(variable,
			CREATE_PTR<BinaryExpression>(CREATE_PTR<VariableExpression>(variable), operation, std::move(result)));*/
		return StatementPtr();
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