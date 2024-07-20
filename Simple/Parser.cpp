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
		result.add(statement());
	}
	return result;
}

StatementPtr Parser::statement() {
	if (match(TokenType::CONST)) {
		StatementPtr result = ConstAssignment();
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
		return Import();

	else if (match(TokenType::SWITCH))
		return Switch();

	else if (match(TokenType::FUNC))
		return std::make_unique<FunctionDefineStatement>(std::move(FunctionDefine()));

	else if (match(TokenType::RETURN))
		return Return();

	else if (get(0).getType() == TokenType::WORD) {
		if (get(1).getType() == TokenType::LPAREN) {
			FunctionStatement result = std::move(Function());
			CHECK_END_STR;
			return std::make_unique<FunctionStatement>(std::move(result));
		}
		else if (get(1).getType() == TokenType::EQ) {
			StatementPtr result = std::move(Assignment());
			CHECK_END_STR;
			return std::move(result);
		}
	}

	else if (get(0).getType() == TokenType::PLUSPLUS || get(0).getType() == TokenType::MINUSMINUS) {
		StatementPtr result = std::move(Assignment());
		CHECK_END_STR;
		return std::move(result);
	}

	/*else if (match(TokenType::NEWLINE))
		return NewLine();*/

	throw Simple_Error("Unknown statement");
}

StatementPtr Parser::statementOrBlock() {
	if (get(0).getType() == TokenType::LBRACE) return block();

	/*const auto& CurrentVariables = Variables::GetAllVariables();
	std::unordered_map<std::string, ValuePtr> VariablesBefore;

	for (auto& var : CurrentVariables)
	{
		VariablesBefore[var.first] = var.second->clone();
	}*/
	return std::make_unique<ShortBlockStatement>(std::move(statement()));
}

//StatementPtr Parser::NewLine() {
//	if (match(TokenType::END_OF_FILE)) return nullptr;
//	line++;
//	return statement();
//}