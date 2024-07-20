#pragma once

#ifndef _PARSER_H_
#define _PARSER_H_

#include "AST.h"
#include "Token.h"

#include <vector>

namespace Simple {
	class Parser {
		std::vector<Token> tokens;
		const size_t size;
		size_t pos;

	public:
		Parser(const std::list<Token>& tokens);

		GlobalBlockStatement parse();

	private:
		friend struct Variables;

		// statements
		StatementPtr block();

		SwitchBlockStatement switchBlock();

		CaseStatement caseStatement();

		StatementPtr statementOrBlock();

		StatementPtr statement();

		StatementPtr Assignment(bool IsConst = false);

		StatementPtr ConstAssignment();

		StatementPtr IfElse();

		StatementPtr DoWhile();

		StatementPtr While();

		StatementPtr For();

		StatementPtr Break();

		StatementPtr Continue();

		StatementPtr Import();

		StatementPtr Switch();

		FunctionDefineStatement FunctionDefine();

		StatementPtr Return();

		//StatementPtr NewLine();

		// expression
		FunctionalExpression Function();

		ExpressionPtr expression();

		ExpressionPtr logicalOr();

		ExpressionPtr logicalAnd();

		ExpressionPtr equality();

		ExpressionPtr conditinal();

		ExpressionPtr additive();

		ExpressionPtr multiplicative();

		ExpressionPtr power();

		ExpressionPtr Unary();

		ExpressionPtr primary();

	private:

		Token get(const size_t relativePosition);

		bool match(const TokenType type);

		Token consume(const TokenType type);

		static int stoihex(const std::string& hex);
	};
}
#endif // !_PARSER_H_