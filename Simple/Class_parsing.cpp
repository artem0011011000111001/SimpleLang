#include "Parser.h"
#include "Method_info.h"
#include "Field_info.h"
#include "ArgParams.h"

using namespace Simple;

StatementPtr Parser::ClassDefine() {

	WString name = consume(TokenType::WORD).getText();

	RawClassFields_decl_t fields_params;
	RawMethod_decl_t methods_params;
	
	bool is_private = true;

	consume(TokenType::LBRACE);

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

			fields_params.emplace(name, MK_PAIR(RawField_info(type_in_str, isImmut, MOVE(defaultValue)), is_private));

			CHECK_END_STR;
		}
		else if (match(TokenType::FUNC)) {

			WString name = consume(TokenType::WORD).getText();

			ArgsParams_t CurrentArgsParam;
			StatementPtr CurrentBody;
			bool Current_is_any_args = false;

			AnalyzeFunction(CurrentArgsParam, CurrentBody, Current_is_any_args);

			methods_params[name].emplace(MK_PAIR(
				static_cast<int>(CurrentArgsParam.size()),
				RawMethod_info(MOVE(CurrentArgsParam), Current_is_any_args, MOVE(CurrentBody), is_private)
			));
		}

		else if (match(TokenType::PUBLIC))  { consume(TokenType::COLON); is_private = false; }
		else if (match(TokenType::PRIVATE)) { consume(TokenType::COLON); is_private = true; }

		else throw Simple_Error("Expected field or method declaration");
	}

	return CREATE_PTR<ClassDefineStatement>(name, MOVE(fields_params), MOVE(methods_params));
}