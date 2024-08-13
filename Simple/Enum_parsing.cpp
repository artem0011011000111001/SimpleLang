#include "Parser.h"

using namespace Simple;

StatementPtr Parser::EnumDefine() {
	WString name = consume(TokenType::WORD).getText();

	WStr_map<RawVariable> fields;

	consume(TokenType::LBRACE);

	while (!match(TokenType::RBRACE)) {

		WString key_name = consume(TokenType::WORD).getText();

		consume(TokenType::EQ);

		fields.emplace(key_name, RawVariable(expression(), true));

		if (match(TokenType::RBRACE))
			break;

		consume(TokenType::COMMA);
	}

	return CREATE_PTR<ObjectDefineStatement>(name, MOVE(fields), true);
}
