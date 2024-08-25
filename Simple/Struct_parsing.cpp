#include "Parser.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Functions.h"
#include "ArgParams.h"
#include "Field_info.h"

using namespace Simple;

StatementPtr Parser::StructDefine() {

	WString name = consume(TokenType::WORD).getText();

	RawFields_decl_t fields_params;
	consume(TokenType::LBRACE);

	Vec<ArgsParams_t> argsParam;
	Vec<StatementPtr> bodies;
	Vec<bool> is_any_args;

	while (!match(TokenType::RBRACE)) {
		if (match(TokenType::_FIELD)) {
			bool isImmut = false;

			if (match(TokenType::IMMUTABLE))
				isImmut = true;

			WString name = consume(TokenType::WORD).getText();

			consume(TokenType::COLON);

			WString type_in_str = consume(TokenType::WORD).getText();

			ExpressionPtr defaultValue;

			if (match(TokenType::EQ))
				defaultValue = expression();

			fields_params.emplace(name, RawField_info(type_in_str, isImmut, MOVE(defaultValue)));

			CHECK_END_STR;
		}
		else if (match(TokenType::FUNC)) {

			if (consume(TokenType::WORD).getText() != L"constructor")
				throw Simple_Error("Constructor name required");

			ArgsParams_t CurrentArgsParam;
			StatementPtr CurrentBody;
			bool Current_is_any_args = false;

			AnalyzeFunction(CurrentArgsParam, CurrentBody, Current_is_any_args);

			argsParam.push_back(MOVE(CurrentArgsParam));
			bodies.push_back(MOVE(CurrentBody));
			is_any_args.push_back(Current_is_any_args);
		}
		else throw Simple_Error("Expected field or constructor declaration");
	}

	return CREATE_PTR<StructDefineStatement>(name, MOVE(argsParam), MOVE(bodies), MOVE(fields_params), is_any_args);
}