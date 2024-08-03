#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Functions.h"

using namespace Simple;

StatementPtr Parser::StructDefine() {
	String name = consume(TokenType::WORD).getText();

	Fields_decl_t fields_params;
	consume(TokenType::LBRACE);

	while (!match(TokenType::RBRACE)) {
		if (match(TokenType::FIELD)) {
			String name = consume(TokenType::WORD).getText();

			consume(TokenType::COLON);

			String type_in_str = consume(TokenType::WORD).getText();
			
			ValueType type = IdentifyValueType(type_in_str);

			fields_params.emplace(name, type);

			CHECK_END_STR;
		}
		else if (match(TokenType::FUNC)) {

			if (consume(TokenType::WORD).getText() != "constructor")
				throw Simple_Error("Constructor name required");

			ArgsParam_t argsParam;
			StatementPtr body;

			AnalyzeFunction(argsParam, body);

			consume(TokenType::RBRACE);

			return CREATE_PTR<ConstructorDefineStatement>(name, argsParam, std::move(body), fields_params);
		}
		else throw Simple_Error("Expected field or constructor declaration");
	}

	return nullptr;
}