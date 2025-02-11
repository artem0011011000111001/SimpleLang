#include "Parser.h"
#include "Simple_Error.h"
#include "Variables.h"
#include "Expressions.h"

#include <algorithm>
#include <iterator>

using namespace Simple;

Parser::Parser(const std::list<Token>& tokens) : size(tokens.size()), pos(0) {
	std::copy(tokens.begin(), tokens.end(), std::back_inserter(this->tokens));
}

GlobalBlockStatement Parser::parse() {
	GlobalBlockStatement result;
	while (!match(TokenType::END_OF_FILE)) {
		result.add(getNextGlobalStatement());
	}
	return result;
}

StatementPtr Parser::getNextGlobalStatement() {

	if (match(TokenType::IMPORT))
		return Import();

	else if (match(TokenType::FUNC))
		return FunctionDefine();

	else if (match(TokenType::STRUCT))
		return StructDefine();

	else if (match(TokenType::ENUM))
		return EnumDefine();

	else if (match(TokenType::CLASS))
		return ClassDefine();

	else return getNextStatement();
}

StatementPtr Parser::getNextStatement() {
	if (match(TokenType::CONST)) {

		StatementPtr result;

		if (match(TokenType::DESTRUCT))
			result = ConstDestructDefine();

		else if (get(2).getType() == TokenType::EQ)
			result = ConstVariableDefine();

		else if (get(2).getType() == TokenType::LBRACE)
			result = ConstObjectDefine();

		CHECK_END_STR;
		return std::move(result);
	}

	else if (match(TokenType::IF))
		return IfElse();

	else if (match(TokenType::ELSE))
		throw Simple_Error("if for else not found");

	else if (match(TokenType::DO))
		return DoWhile();

	else if (match(TokenType::WHILE))
		return While();

	else if (match(TokenType::FOR))
		return For();

	else if (match(TokenType::FOREACH))
		return ForEach();

	else if (match(TokenType::BREAK))
		return Break();

	else if (match(TokenType::CONTINUE))
		return Continue();

	else if (match(TokenType::IMPORT))
		throw Simple_Error("Cannot be imported not in global visibility", line);

	else if (match(TokenType::SWITCH))
		return Switch();

	else if (match(TokenType::RETURN))
		return Return();

	else if (match(TokenType::STRUCT))
		throw Simple_Error("You cannot declare a struct not in global visibility", line);

	else if (match(TokenType::_FIELD))
		throw Simple_Error("Keyword field cannot be used here", line);

	else if (match(TokenType::TRY))
		return TryCatch();

	else if (match(TokenType::CATCH))
		throw Simple_Error("Keyword catch cannot be used here", line);

	else if (match(TokenType::FINALLY))
		throw Simple_Error("Keyword finally cannot be used here", line);

	else if (match(TokenType::THROW)) {
		StatementPtr result = Throw();
		CHECK_END_STR;
		return MOVE(result);
	}

	else if (match(TokenType::DESTRUCT)) {
		StatementPtr result = DestructDefine();
		CHECK_END_STR;
		return MOVE(result);
	}

	else if (match(TokenType::ENUM))
		throw Simple_Error("You cannot declare a enum not in global visibility", line);

	else if (get(0).getType() == TokenType::WORD) {
		if (get(1).getType() == TokenType::EQ) {
			StatementPtr result = VariableDefine();
			CHECK_END_STR;
			return MOVE(result);
		}
		else if (get(1).getType() == TokenType::LBRACE) {
			StatementPtr result = ObjectDefine();
			CHECK_END_STR;
			return MOVE(result);
		}
	}

	ExpressionPtr expr = MOVE(expression());

	Token CurrentToken = get(0);
	if (CurrentToken.getType() == TokenType::EQ ||
		CurrentToken.getType() == TokenType::PLUSEQ ||
		CurrentToken.getType() == TokenType::MINUSEQ ||
		CurrentToken.getType() == TokenType::STAREQ ||
		CurrentToken.getType() == TokenType::SLASHEQ ||
		CurrentToken.getType() == TokenType::STARSTAREQ
		) {
		StatementPtr result = Assignment(MOVE(expr));
		CHECK_END_STR;
		return MOVE(result);
	}

	else CHECK_END_STR;
	return CREATE_PTR<ExpressionStatement>(MOVE(expr));
}

StatementPtr Parser::statementOrBlock() {
	if (get(0).getType() == TokenType::LBRACE) return block();

	return CREATE_PTR<ShortBlockStatement>(MOVE(getNextStatement()));
}

//StatementPtr Parser::NewLine() {
//	if (match(TokenType::END_OF_FILE)) return nullptr;
//	line++;
//	return statement();
//}