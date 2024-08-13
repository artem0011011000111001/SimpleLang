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
		size_t line = 1;

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

		StatementPtr getNextGlobalStatement();

		StatementPtr getNextStatement();

		StatementPtr Assignment(ExpressionPtr expr);

		StatementPtr IfElse();

		StatementPtr DoWhile();

		StatementPtr While();

		StatementPtr For();

		StatementPtr ForEach();

		StatementPtr Break();

		StatementPtr Continue();

		StatementPtr Import();

		StatementPtr Switch();

		StatementPtr VariableDefine(bool isConst = false);

		StatementPtr ObjectDefine(bool isConst = false);

		StatementPtr ConstVariableDefine();

		StatementPtr ConstObjectDefine();

		StatementPtr ConstDestructDefine();

		void AnalyzeFunction(ArgsParams_t& argsParams, StatementPtr& body, bool& is_any_args);

		StatementPtr FunctionDefine();

		StatementPtr StructDefine();

		StatementPtr EnumDefine();

		StatementPtr Return();

		StatementPtr TryCatch();

		StatementPtr Throw();

		StatementPtr DestructDefine(bool isConst = false);

		//StatementPtr NewLine();

		// expression
		ExpressionPtr Function();

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

		void skip_newlines();

		Token get(const size_t relativePosition);

		bool match(const TokenType type);

		Token consume(const TokenType type);

		static int stoihex(const WString& hex);
	};
}
#endif // !_PARSER_H_