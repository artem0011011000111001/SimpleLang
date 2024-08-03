#include "Parser.h"
#include "Simple_Error.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::VariableDefine(bool isConst) {

	String name = consume(TokenType::WORD).getText();

	consume(TokenType::EQ);

	ExpressionPtr expr = expression();

	return CREATE_PTR<VariableDefineStatement>(name, std::move(expr), isConst);
}

StatementPtr Parser::ObjectDefine(bool isConst) {
	
	String name = consume(TokenType::WORD).getText();

	consume(TokenType::LBRACE);

	Str_map<ExpressionPtr> fields;

	while (!match(TokenType::RBRACE)) {
		String field_name = consume(TokenType::WORD).getText();

		consume(TokenType::COLON);

		fields.emplace(field_name, expression());
	}

	return CREATE_PTR<ObjectDefineStatement>(name, std::move(fields), isConst);
}

StatementPtr Parser::ConstVariableDefine() {
	return VariableDefine(true);
}

StatementPtr Parser::ConstObjectDefine() {
	return ObjectDefine(true);
}