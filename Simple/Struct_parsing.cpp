#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Functions.h"
#include "ArgParams.h"
#include "Field_decl.h"

using namespace Simple;

StatementPtr Parser::StructDefine() {
	WString name = consume(TokenType::WORD).getText();

	RawFields_decl_t fields_params;
	consume(TokenType::LBRACE);

	StatementPtr constructor;

	while (!match(TokenType::RBRACE)) {
		if (match(TokenType::_FIELD)) {
			bool isImmut = false;

			if (match(TokenType::IMMUTABLE))
				isImmut = true;

			WString name = consume(TokenType::WORD).getText();

			consume(TokenType::COLON);

			WString type_in_str = consume(TokenType::WORD).getText();
			
			//ValueType type = IdentifyValueType(type_in_str);

			ExpressionPtr defaultValue = nullptr;

			if (match(TokenType::EQ))
				defaultValue = expression();

			fields_params.emplace(name, RawField_decl(type_in_str, isImmut, MOVE(defaultValue)));

			CHECK_END_STR;
		}
		else if (match(TokenType::FUNC)) {

			if (consume(TokenType::WORD).getText() != L"constructor")
				throw Simple_Error("Constructor name required");

			ArgsParams_t argsParam;
			StatementPtr body;
			bool is_any_args = false;

			AnalyzeFunction(argsParam, body, is_any_args);

			constructor = CREATE_PTR<ConstructorDefineStatement>(name, MOVE(argsParam), MOVE(body), MOVE(fields_params), is_any_args);
		}
		else throw Simple_Error("Expected field or constructor declaration");
	}

	return constructor;
}