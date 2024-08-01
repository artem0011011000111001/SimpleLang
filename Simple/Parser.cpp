#include "Parser.h"
#include "Simple_Error.h"
#include "Variables.h"
#include "Expressions.h"

#include <algorithm>
#include <iterator>

using namespace Simple;

Parser::Parser(const std::list<Token>& tokens) : size(tokens.size()), pos(0) {
	std::copy(tokens.begin(), tokens.end(), std::back_inserter(this->tokens));
	//for (const auto& token : tokens)
	//{
	//	this->tokens.push_back(token);
	//}
}

GlobalBlockStatement Parser::parse() {
	GlobalBlockStatement result;
	while (!match(TokenType::END_OF_FILE)) {
		/*StatementPtr CurrentStatement = statement();
		CurrentStatement->execute();
		result.add(std::move(CurrentStatement));*/
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

	else return getNextStatement();
}

StatementPtr Parser::getNextStatement() {
	if (match(TokenType::CONST)) {
		StatementPtr result;
		if (get(2).getType() == TokenType::EQ)
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

	else if (match(TokenType::BREAK))
		return Break();

	else if (match(TokenType::CONTINUE))
		return Continue();

	else if (match(TokenType::IMPORT))
		throw Simple_Error("Cannot be imported not in global visibility", line);

	else if (match(TokenType::SWITCH))
		return Switch();

	else if (match(TokenType::FUNC))
		throw Simple_Error("You cannot declare a function not in global visibility", line);

	else if (match(TokenType::RETURN))
		return Return();

	else if (match(TokenType::STRUCT))
		throw Simple_Error("You cannot declare a struct not in global visibility", line);

	else if (match(TokenType::FIELD))
		throw Simple_Error("Keyword field cannot be used here");

	else if (match(TokenType::TRY))
		return TryCatch();

	else if (match(TokenType::THROW)) {
		StatementPtr result = Throw();
		CHECK_END_STR;
		return std::move(result);
	}

	else if (get(0).getType() == TokenType::WORD) {
		if (get(1).getType() == TokenType::EQ) {
			StatementPtr result = VariableDefine();
			CHECK_END_STR;
			return std::move(result);
		}
		else if (get(1).getType() == TokenType::LBRACE) {
			StatementPtr result = ObjectDefine();
			CHECK_END_STR;
			return std::move(result);
		}
	}

	ExpressionPtr expr = std::move(expression());

	Token CurrentToken = get(0);
	if (CurrentToken.getType() == TokenType::EQ ||
		CurrentToken.getType() == TokenType::PLUSEQ ||
		CurrentToken.getType() == TokenType::MINUSEQ ||
		CurrentToken.getType() == TokenType::STAREQ ||
		CurrentToken.getType() == TokenType::SLASHEQ ||
		CurrentToken.getType() == TokenType::STARSTAREQ
		) {
		StatementPtr result = Assignment(std::move(expr));
		CHECK_END_STR;
		return std::move(result);
	}

	else CHECK_END_STR;
	return CREATE_PTR<ExpressionStatement>(std::move(expr));
}

StatementPtr Parser::statementOrBlock() {
	if (get(0).getType() == TokenType::LBRACE) return block();

	/*const auto& CurrentVariables = Variables::GetAllVariables();
	std::unordered_map<std::string, ValuePtr> VariablesBefore;

	for (auto& var : CurrentVariables)
	{
		VariablesBefore[var.first] = var.second->clone();
	}*/
	return CREATE_PTR<ShortBlockStatement>(std::move(getNextStatement()));
}

//StatementPtr Parser::NewLine() {
//	if (match(TokenType::END_OF_FILE)) return nullptr;
//	line++;
//	return statement();
//}