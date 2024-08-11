#include "Parser.h"
#include "Simple_Error.h"
#include "Simple_defines.h"
#include "RawVariable.h"

using namespace Simple;

StatementPtr Parser::VariableDefine(bool isConst) {

	WString name = consume(TokenType::WORD).getText();

	consume(TokenType::EQ);

	ExpressionPtr expr = expression();

	return CREATE_PTR<VariableDefineStatement>(name, std::move(expr), isConst);
}

StatementPtr Parser::ObjectDefine(bool isConst) {

	WString name = consume(TokenType::WORD).getText();

	consume(TokenType::LBRACE);

	WStr_map<RawVariable> fields;

	while (!match(TokenType::RBRACE)) {
		bool isConst = false;

		if (match(TokenType::IMMUTABLE))
			isConst = true;

		WString field_name = consume(TokenType::WORD).getText();

		consume(TokenType::COLON);

		fields.emplace(field_name, RawVariable(expression(), isConst));

		if (match(TokenType::RBRACE))
			break;

		consume(TokenType::COMMA);
	}

	return CREATE_PTR<ObjectDefineStatement>(name, MOVE(fields), isConst);
}

StatementPtr Parser::DestructDefine(bool isConst) {

	WStr_vec fields_names;
	while (true) {
		fields_names.push_back(consume(TokenType::WORD).getText());

		if (!match(TokenType::RPAREN))
			consume(TokenType::COMMA);
	}

	WString obj_name = consume(TokenType::WORD).getText();

	return CREATE_PTR<DestructDefineStatement>(fields_names, obj_name, isConst);
}

StatementPtr Parser::ConstVariableDefine() {
	return VariableDefine(true);
}

StatementPtr Parser::ConstObjectDefine() {
	return ObjectDefine(true);
}

StatementPtr Parser::ConstDestructDefine() {
	return DestructDefine(true);
}