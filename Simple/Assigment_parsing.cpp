#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

StatementPtr Parser::Assignment(ExpressionPtr expr) {

	if (match(TokenType::EQ)) {
		ExpressionPtr expr2 = expression();

		return CREATE_PTR<AssigmentStatement>(std::move(expr), std::move(expr2));
	}

	auto OPEREQ = [this, &expr](const BinaryOperators operation) -> StatementPtr {
		ExpressionPtr expr2 = expression();
		return CREATE_PTR<AbbreviatedOperationsStatement>(std::move(expr), operation, std::move(expr2));
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